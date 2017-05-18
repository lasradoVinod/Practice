#include <iostream>
#include <vector>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

using namespace std;

int usr_intC = 0;


int child()
{
	cout << "This is the child with pid " << getpid() << " and parent pid " << getppid() << endl;
	sleep(3);
	exit(0);
}
int main()
{
	int ret;

	int fd[2];

	
	ret = fork();

	if(ret == -1)
	{
		cerr <<"Fork error";
	}

	if(ret == 0)
	{
		child();
	}
	else 
	{
		cout << "This is the parent with pid " << getpid() << " and child pid " << ret << endl;	
		wait(&ret);
	}

	cout << "Just Checking";
}
