#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/select.h>
#include <sys/time.h>


#define PEER_PORT		4268
#define BUFF_SIZE		1024
#define RETRY			5
#define WINDOW_SIZE		5
#define START			0x0A
#define MOD_SEQNUM		128
#define INC(seqNum)		(seqNum = (seqNum + 1 ) % MOD_SEQNUM)
#define TIMEOUT			3 /*sec*/

typedef struct Queue
{
	uint8_t head;
	uint8_t tail;
	uint8_t count;
}Queue;

Queue q;

void initQueue()
{
	q.head = 0;
	q.tail = 0;
	q.count = 0;
}

int getFreeIndex()
{
	int temp;
	if (q.count < WINDOW_SIZE)
	{
		if (q.count != 0)
			q.tail = (q.tail + 1) % WINDOW_SIZE;
		q.count ++;
		return q.tail;
	}
	return -1;
}

int dequeue()
{
	if (q.count == 0)
	{
		return -1;
	}
	else
	{
		q.count --;
		if(q.count != 0)
		{
			q.head = (q.head + 1) % WINDOW_SIZE;
		}
		else
		{
			q.head = q.tail;
		}
	}
	return 0;
}

int initSocket()
{
	int socketfd,yes;
	socklen_t lenStruct;
	struct sockaddr_in myAddress;
	if ((socketfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
		perror("socket not created");
		exit(1);
	}

	if (setsockopt(socketfd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int)) == -1) {
		perror("setsockopt");
		exit(1);
	}

	myAddress.sin_family = AF_INET;
	myAddress.sin_port = htons(PEER_PORT);

	memset(myAddress.sin_zero, '\0', sizeof myAddress.sin_zero);
	inet_aton("127.0.0.1",&(myAddress.sin_addr));

	lenStruct = sizeof (struct sockaddr_in);
	connect (socketfd,(struct sockaddr *)&myAddress,lenStruct);

	printf("Connection Done");
	return socketfd;
}

uint8_t waitForAck(int socketfd)
{
	uint8_t ack;
	struct timeval tv,ctv;
	int retval;
	int8_t tempVal = RETRY;

	do
	{
		gettimeofday(&tv,NULL);
		tv.tv_sec += RETRY;
		do{
			retval = recv(socketfd,&ack,1,MSG_DONTWAIT);
			gettimeofday(&ctv,NULL);
		}while((retval < 0) && (((int)tv.tv_sec - (int)ctv.tv_sec) > 0));

       	if (retval >= 0)
       		break;
       	else
       	{
       		tempVal --;
	    }
	}while(tempVal > 0);
	if (tempVal == 0)
	{
		perror("Connection Failed");
		exit(1);
	}
	return ack;
}

void sendFile(const char * fileName, int socketfd)
{
	int8_t retval;
	uint8_t ack,seqNum;
	uint8_t buffer [BUFF_SIZE] = {0};
	size_t readBytes;
	FILE * fp;


	fp = fopen(fileName,"rb");
	if(fp == NULL)
	{
		perror("Cannot open File");
		exit(1);
	}

	seqNum = ((uint8_t)rand() % MOD_SEQNUM);
	buffer[0] = seqNum;
	readBytes = fread(&buffer[1],1,BUFF_SIZE-1,fp);
	while(readBytes)
	{
		printf ("seqNum %d %d", seqNum,ack);
		retval = send(socketfd,buffer,readBytes+1,0);
		if(retval == -1)
		{
			perror("Sending Error");
			exit(1);
		}

		ack = waitForAck(socketfd);
		
		if(ack == seqNum)
		{
			printf ("Recieved ack \n");
			readBytes = fread(&buffer[1],1,BUFF_SIZE-1,fp);
			INC(seqNum);
			buffer[0] = seqNum;
		}
	}

	printf("Done Sending\n");
	buffer[0] = (1 << 7) ;
	send(socketfd,buffer,1,0);
	fclose(fp);
}

void sendFileGOBackN(const char * fileName, int socketfd)
{
	int pos;
	int pacSize [WINDOW_SIZE] = {0};
	uint8_t buffer [WINDOW_SIZE][BUFF_SIZE] = {{0}};
	uint8_t ack, SendData ;
	FILE * fp;
   	struct timeval tv,ctv,lastTv;
   	int retval;
   	uint8_t sendPos;
	fp = fopen(fileName,"rb");
	uint8_t seqNum,currSeqNum;
	int readBytes;
	uint8_t retry = RETRY;

	if(fp == NULL)
	{
		perror("Cannot open File");
		exit(1);
	}

	/*Start the communication*/
	seqNum = ((uint8_t)rand() % MOD_SEQNUM);
	buffer[0][0] = START;
	buffer[0][1] = seqNum;
	retval = send(socketfd,buffer,2,0);
	ack = waitForAck(socketfd);

	if(ack != seqNum)
	{
		printf("Client not ready to recieve\n");
		return;
	}

	INC(seqNum);

	currSeqNum =  seqNum;

	pos = getFreeIndex();
	readBytes = fread(&buffer[pos][1],1,BUFF_SIZE-1,fp);
	buffer[pos][0] = seqNum;
	pacSize[pos] = readBytes + 1;
	INC(seqNum);
	sendPos = 0;
	SendData = 1;
	gettimeofday(&tv,NULL);
	while(readBytes || (q.count == 0))
	{
		if(SendData)
		{
			printf ("Sending %d\n", buffer[sendPos][0]);
			retval = send(socketfd,buffer[sendPos],pacSize[sendPos],0);
			if(retval == -1)
			{
				perror("Sending Error");
				exit(1);
			}
		}

		if(sendPos != q.tail)
		{
			sendPos = (sendPos + 1) % WINDOW_SIZE;
		}
		else
		{
			SendData = 0;
		}

		retval = recv(socketfd,&ack,1,MSG_DONTWAIT);
		if (retval != -1)
		{
			if(ack == currSeqNum)
			{
				dequeue();
				gettimeofday(&tv,NULL);
				INC(currSeqNum);
			}
		}

		gettimeofday(&ctv,NULL);

		if((int)ctv.tv_sec - (int)tv.tv_sec > TIMEOUT)
		{
			printf("Retrying\n");
			sendPos = q.head;
			SendData = 1;
			if(retry == 0)
			{
				perror ("Connection Failed");
				exit(1);
			}
			if((lastTv.tv_sec - tv.tv_sec) < TIMEOUT + 1)
				retry --;
			lastTv = tv;
			gettimeofday(&tv,NULL);
		}

		pos = getFreeIndex();
		if(pos != -1)
		{
			readBytes = fread(&buffer[pos][1],1,BUFF_SIZE-1,fp);
			buffer[pos][0] = seqNum;
			pacSize[pos] = readBytes + 1;
			INC(seqNum);
			SendData = 1;
		}
	}
	/*Stop the communication*/
	buffer[0][0] = 0 | (1 << 7);
	buffer[0][0] |= seqNum;
	retval = send(socketfd,buffer[0],1,0);

	if(retval == -1)
	{
		perror("Sending Error");
		exit(1);
	}

	fclose (fp);
}
int main()
{
	int socketfd = initSocket();
	setbuf(stdout,NULL);
	initQueue();
	/*sendFile("Input.pdf",socketfd);*/
	sendFileGOBackN("/home/vinod/Practice/Practice/Socket/Input.pdf",socketfd);
	close(socketfd);
	return 0;
}
