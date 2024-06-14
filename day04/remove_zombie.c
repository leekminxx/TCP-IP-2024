/*# date : 2024-06-14
	# file : remove_zombie.c
	# desc : 시그널 핸들링을통한 좀비 프로세스의 소멸
----------------------------------------------
시그널 SIGCHLD에 대한 시그널 핸들러의 등록과정
시그널 SIGHLD 의 발생을 대기하기 위해서 부모 프로세스를 5초간 5회 멈춰놓았음
시그널이 발생하면 부모 프로세스는 깨어나기 때문에 실제 멈춰있는 시간은 25초가 되지 않음
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void read_childproc(int sig)
{
	int status;
	pid_t id=waitpid(-1, &status, WNOHANG);
	if(WIFEXITED(status))
	{
		printf("Removed proc id: %d \n", id);
		printf("Child send: %d \n", WEXITSTATUS(status));
	}
}

int main(int argc, char *argv[])
{
	pid_t pid;
	struct sigaction act;
	act.sa_handler=read_childproc;
	sigemptyset(&act.sa_mask);
	act.sa_flags=0;
	sigaction(SIGCHLD, &act, 0);

	pid=fork();
	if(pid==0)
	{
		puts("Hi! I'm child process");
		sleep(10);
		return 12;
	}
	else
	{
		printf("Child proc id: %d \n", pid);
		pid=fork();
		if(pid==0)
		{
			puts("Hi! I'm child process");
			sleep(10);
			exit(24);
		}
		else
		{
			int i;
			printf("Child proc id: %d \n", pid);
			for(i=0; i<5; i++)
			{
				puts("wait...");
				sleep(5);
			}
		}
	}
	return 0;
}


