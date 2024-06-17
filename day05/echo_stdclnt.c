/* day02/echo_client.c 에서는 수신된 데이터를 문자열로 구성하는 과정이 필요했지만
	 (데이터의 마지막에 0 삽입하는 과정 필요했음)
	 아래의 코드는 표준 입출력 함수의 사용으로 문자열 단위로 데이터를 송수신하기에
	 이런 과정이 생략되었다!
  */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define BUF_SIZE 1024
void error_handling(char* message);

int main(int argc, char* argv[])
{
	int sock;
	char message[BUF_SIZE];
	int str_len;
	struct sockaddr_in serv_adr;

	FILE *readfp;
	FILE *writefp;
	if(argc != 3) {
		printf("Usage : %s <IP> <port>\n", argv[0]);
		exit(1);
	}

	sock = socket(PF_INET, SOCK_STREAM, 0);
	if(sock == -1)
		error_handling("socket() error");

	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_adr.sin_port = htons(atoi(argv[2]));

	if(connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
		error_handling("connect() error");
	else
		puts("Connected ..... ");

	readfp = fdopen(sock, "r");
	writefp = fdopen(sock, "w");
	while(1)
	{
		fputs("Input message(Q to quit) : ", stdout);
		fgets(message, BUF_SIZE, stdin);

		if(!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
			break;

		fputs(message, writefp);
		fflush(writefp);
		fgets(message, BUF_SIZE, readfp);
		printf("Message from server : %s", message);
	}
	fclose(writefp);
	fclose(readfp);
	return 0;
}

void error_handling(char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
