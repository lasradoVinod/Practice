#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>

#define MY_PORT			4268
#define BUFF_SIZE		1024
#define START			0x0A
#define MOD_SEQNUM		128

#define INC(seqNum)		(seqNum = (seqNum + 1 ) % MOD_SEQNUM)

typedef enum
{
	enStart,
	enRecv,
	enStop
}State;
int initSocket()
{
	int optval;

	struct sockaddr_in myAddress;
	int socketfd;

	if ((socketfd = socket(PF_INET,SOCK_DGRAM,0)) == -1 )
	{
		perror("Socket creation failed");
		exit(1);
	}

	myAddress.sin_family = AF_INET;
	myAddress.sin_port = htons(MY_PORT);

	memset(myAddress.sin_zero, '\0', sizeof myAddress.sin_zero);

	inet_aton("127.0.0.1",&(myAddress.sin_addr));

	optval = 1;
	if (setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof optval) == -1)
	{
		perror ("Setting socket Options Failed");
		exit(1);
	}

	if (bind(socketfd,(struct sockaddr *)&myAddress,sizeof(myAddress)) == -1)
	{
		perror("Bind Failed");
		exit(1);
	}
	return socketfd;
}

void recvFile(int socketfd)
{
	uint8_t seqNum,prevSeqNum;
	int len;
	int retVal;
	socklen_t lenStruct;
	FILE * fp;
	struct sockaddr_in peerAddress;	
	uint8_t msg[BUFF_SIZE] = {0};
	uint8_t ack = 1;
	fp = fopen("Output.pdf","wb");
	lenStruct = sizeof (sockaddr_in);
	len = recvfrom(socketfd,msg,BUFF_SIZE,0,(struct sockaddr *)&peerAddress,&lenStruct);
	seqNum = msg[0];
	printf("msg %d",msg[0]);
	ack = seqNum;
	prevSeqNum = (seqNum - 1) % MOD_SEQNUM;

	retVal = sendto(socketfd,&ack,1,0,(struct sockaddr *)&peerAddress,lenStruct);
	if(retVal == -1)
	{
		perror("Sending Failed");
		exit(1);
	}
	while(!(msg[0] & (1 << 7)))
	{	
		printf ("seqNum %d", seqNum);
		if(seqNum == msg[0])
		{
			fwrite(&msg[1],1,len-1,fp);
			prevSeqNum = seqNum;
			INC(seqNum);
		}

		len = recvfrom(socketfd,msg,BUFF_SIZE,0,(struct sockaddr *)&peerAddress,&lenStruct);

		retVal = sendto(socketfd,msg,1,0,(struct sockaddr *)&peerAddress,lenStruct);
		if(retVal == -1)
		{
			perror("Sending Failed");
			exit(1);
		}
	}
	fclose(fp);
}

void recvFileGoBackN(int socketfd)
{
	int temp;
	int len;
	int retVal;
	socklen_t lenStruct;
	FILE * fp;
	struct sockaddr_in peerAddress;	
	uint8_t msg[BUFF_SIZE] = {0};
	uint8_t ack = 1;
	uint8_t seqNum,prevSeqNum;
	uint8_t done = 1;
	State state = enStart;

	fp = fopen("Output.pdf","wb");
	lenStruct = sizeof (sockaddr_in);

	while(done)
	{
		len = recvfrom(socketfd,msg,BUFF_SIZE,0,(struct sockaddr *)&peerAddress,&lenStruct);
		switch(state)
		{
			case enStart:
				if (len == 2 && msg[0] == (char)START)
				{
					ack = msg[1];
					retVal = sendto(socketfd,&ack,1,0,(struct sockaddr *)&peerAddress,lenStruct);
					if(retVal == -1)
					{
						perror("Sending Failed");
						exit(1);
					}
					state = enRecv;
					prevSeqNum = msg[1];
					seqNum = (prevSeqNum + 1) % MOD_SEQNUM;
				}
				break;

			case enRecv:
				temp = msg[0] & (1 << 7);
				printf("In recv %x  %d\n",msg[0], temp);
				if(temp == 128)
				{
					printf ("Ending Communication");
					done = 0;
					ack = msg[0] & 0x7F;
					retVal = sendto(socketfd,&ack,1,0,(struct sockaddr *)&peerAddress,lenStruct);
					if(retVal == -1)
					{
						perror("Sending Failed");
						exit(1);
					}
					break;
				}
				if((msg[0] & 0x7F) == seqNum)
				{
					retVal = fwrite(&msg[1],1,len-1,fp);
					if(retVal == -1)
					{
						perror("Write Failed");
						exit(1);
					}
					ack = seqNum;
					prevSeqNum = seqNum;
					INC(seqNum);

					retVal = sendto(socketfd,&ack,1,0,(struct sockaddr *)&peerAddress,lenStruct);
					if(retVal == -1)
					{
						perror("Sending Failed");
						exit(1);
					}
				}
				if((msg[0] & 0x7F) == ((seqNum - 5) % MOD_SEQNUM))
				{
					ack = prevSeqNum;
					retVal = sendto(socketfd,&ack,1,0,(struct sockaddr *)&peerAddress,lenStruct);
					if(retVal == -1)
					{
						perror("Sending Failed");
						exit(1);
					}	
				}
				break;
		}
	}
	fclose(fp);
}


int main()
{
	int socketfd = initSocket();
	setbuf(stdout,NULL);
	recvFileGoBackN(socketfd);
	close(socketfd);
	return 0;
}
