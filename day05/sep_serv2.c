/* sep_clnt.c와 함께 실행  */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define BUF_SIZE 1024

int main(int argc, char* argv[])
{
	int serv_sock, clnt_sock;
	FILE *readfp;
	FILE *writefp;

	struct sockaddr_in serv_adr, clnt_adr;
	socklen_t clnt_adr_sz;
	char buf[BUF_SIZE] = {0,};

	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_adr.sin_port = htons(atoi(argv[1]));

	bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr));
	listen(serv_sock, 5);
	clnt_adr_sz = sizeof(clnt_adr);
	clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);

	// fdopen 함수 호출을 통해 FILE 포인터 생성
	readfp = fdopen(clnt_sock, "r");
	// dup 함수 호출의 반환 값을 대상으로 FILE 포인터 생성하므로
	// 복사한 파일 디스크립터를 기반으로 쓰기 모드의 FILE 포인터 생성!
	writefp = fdopen(dup(clnt_sock), "w");

	fputs("FROM SERVER : Hi client? \n", writefp);
	fputs("I love all of the world \n", writefp);
	fputs("You are awesome! \n", writefp);
	fflush(writefp);

	// fileno 함수호출 시 반환되는 파일 디스크립터를 대상으로 shutdown 함수 호출
	// Half-close 진행되어
	// 클라이언트로 EOF 전달됨
	// shutdown 함수가 호출되면 복사된 파일 디스크립터의 수에 상관없이 Half-close 진행되고
	// 이 과정에서 EOF도 전달됨!!
	shutdown(fileno(writefp), SHUT_WR);
	fclose(writefp);

	fgets(buf, sizeof(buf), readfp);
	fputs(buf, stdout);
	fclose(readfp);
	return 0;
}
