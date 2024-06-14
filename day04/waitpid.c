/*
# date : 2024-06-14
# file : waitpid.c
# desc : 좀비 프로세스의 소멸2 : wait 함수의 사용
---------------------------------------------------
 자식 프로세스의 종료를 늦추기 위해서 sleep 함수를 사용 호출
이것으로 15초간의 지연이 발생
while 문 내에서waitpid 함수를 호출 세번째 인자로 WNOHANG을 전달하여 종료된 자식 프로세스가 없으면 0을 반환

*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	int status;
	pid_t pid=fork();
	if(pid==0)
	{
		sleep(15);
		return 24;
	}
	else
	{
		while(!waitpid(-1, &status, WNOHANG))
		{
			sleep(3);
			puts("sleep 3sec.");
		}

		if(WIFEXITED(status))
			printf("Child send %d \n", WEXITSTATUS(status));
	}
	return 0;
}
