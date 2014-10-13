#include <iostream>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstring>

using namespace std;
int shmid;

const char  *ptr = "This is shared memory test";
#define SHM_SIZE 1000
#define SHM_MODE 0600

int shared_memory(void);
int main()
{
	shared_memory();
	exit(0);
}

int shared_memory(void)
{
	pid_t pid;
	void  *shmptr;

	if ((shmid = shmget(IPC_PRIVATE, SHM_SIZE, SHM_MODE)) < 0)
	{
		cout<<"Shared memory get error"<<endl;
		exit(0);
	}

	cout<<"==========="<<endl;
	if((pid = fork()) < 0 )
	{
		cout<<"Create new process failed"<<endl;
		exit(0);
	}
	else if (pid > 0)
	{
		cout<<"In parent process"<<endl;
		if ((shmptr = shmat(shmid, 0, 0)) == (void *)-1)
		{
			cout<<"Map shared memory failed"<<endl;
			exit(0);
		}
		else
		{
			memset(shmptr, 0, SHM_SIZE-1);
			memcpy(shmptr, ptr, 30);
		}

	}
	else
	{
		cout<<"In child process"<<endl;
		sleep(2);
		if ((shmptr = shmat(shmid, 0, 0)) == (void *)-1)
		{
			cout<<"Map shared memory failed"<<endl;
			exit(0);
		}

		cout<<(char*)shmptr<<endl;
	}

	return 0;
}
