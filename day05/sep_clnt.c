#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define BUF_SIZE 1024

int main(int argc, char* argv[])
{
	int sock;
	char buf[BUF_SIZE];
	struct sockaddr_in serv_addr;

	FILE *readfp;
	FILE *writefp;

	sock = socket(PF_INET, SOCK_STREAM, 0);
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_port = htons(atoi(argv[2]));

	connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

	// 표준 입출력 함수의 호출을 위해 읽기모드 FILE 포인터
	readfp = fdopen(sock, "r");
	// 쓰기모드 FILE 포인터 생성
	writefp = fdopen(sock, "w");

	while(1)
	{
		// EOF 전달되면 fgets 함수는 NULL 포인터 반환!
		// NULL이 반환되는 경우 반복문 탈출
		if(fgets(buf, sizeof(buf), readfp) == NULL)
			break;
		fputs(buf, stdout);
		fflush(stdout);
	}

	// 서버로 문자열 전송
	// 이 문자열은 서버로부터 전달된 EOF 수신 후 전송하는 문자열!!
	fputs("FROM CLIENT : Thank you! \n", writefp);
	fflush(writefp);
	fclose(writefp);
	fclose(readfp);
	return 0;
}
