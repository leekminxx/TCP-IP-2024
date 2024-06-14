/*
# date : 2024-06-14
# file : pipe1.c
# desc : 파이프(PIPE) 기반의 프로세스간 통신
----------------------------------------------
pipe 함수호출을 통해서 파이프를 생성 이로 인해서 배열fds에는 입출력을 위한 파일 디스크립터가 각각 저장
fork  함수를 호출 두 개의 파일 디스크립터를 함께 소유 이로써 부모와 자식 프로세스가 동시에 입출력 파일 디스크립터를 모두 소유
자식 프로세스는 30행 실행을 통해서 파이프로 문자열을 전달
그리고  부모 프로세스는 35 행을 통해서 문자열을 수신
*/


#include <stdio.h>
#include <unistd.h>
#define BUF_SIZE 30

int main(int argc, char *argv[])
{
	int fds[2];
	char str[]="Who are you?";
	char buf[BUF_SIZE];
	pid_t pid;
	
	pipe(fds);
	pid=fork();
	if(pid==0)
	{
		write(fds[1], str, sizeof(str));
	}
	else
	{
		read(fds[0], buf, BUF_SIZE);
		puts(buf);
	}
	return 0;
}
