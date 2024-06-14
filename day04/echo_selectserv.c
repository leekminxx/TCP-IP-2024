/*
# date : 2024-06-14
# file : echo_selectserv.c
# desc : 멀티플렉싱 서버의 구현
-------------------------------
- select 함수의 두 번째 인자로 전달될 fd_set형 변수 reads에 서버 소켓을 등록하고 있음
이로써 데이터의 수신여부를 관찰하는 관찰대상에 서버 소켓이 포함됨 
- while문으로 구성된 무한루프 내에서 select함수가 호출 select함수의 세번째 그리고네 번쨰 매개변수가 비어있음 
- 69 , 71 행은 select 함수가 1이상 반환했을 때 실행되는 반복문 1이상 반환되었으므로  FD_ISSET함수를 호출하면서 상태변화가 있었던 파일 스크립터(수신된 데이터가 있는 소켓)을 찾고있음
- 상태 변화가 확인이 되면 제일먼저서버 소켓에서 변화가있었는지 확인 그리고 서버 소켓의 상태변화가 맞으면 이어서 연결요청에 대한 수락의 과정을 진행 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/select.h>

#define BUF_SIZE 100
void error_handling(char *buf);

int main(int argc, char *argv[])
{
	int serv_sock, clnt_sock;
	struct sockaddr_in serv_adr, clnt_adr;
	struct timeval timeout;
	fd_set reads, cpy_reads;

	socklen_t adr_sz;
	int fd_max, str_len, fd_num, i;
	char buf[BUF_SIZE];
	if(argc!=2) {
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}
	serv_sock=socket(PF_INET, SOCK_STREAM, 0);
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family=AF_INET;
	serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_adr.sin_port=htons(atoi(argv[1]));

	if(bind(serv_sock, (struct sockaddr*) &serv_adr, sizeof(serv_adr))==-1)
		error_handling("bind() error");
	if(listen(serv_sock, 5)==-1)
		error_handling("listen() error");

	FD_ZERO(&reads);
	FD_SET(serv_sock, &reads);
	fd_max=serv_sock;

	while(1)
	{
		cpy_reads=reads;
		timeout.tv_sec=5;
		timeout.tv_usec=5000;

		if((fd_num=select(fd_max+1, &cpy_reads, 0, 0, &timeout))==-1)
			break;

		if(fd_num==0)
			continue;

		for(i=0; i<fd_max+1; i++)
		{
			if(FD_ISSET(i, &cpy_reads))
			{
				if(i==serv_sock)     // connection request!
				{
					adr_sz=sizeof(clnt_adr);
					clnt_sock=
						accept(serv_sock, (struct sockaddr*)&clnt_adr, &adr_sz);
					FD_SET(clnt_sock, &reads);
					if(fd_max<clnt_sock)
						fd_max=clnt_sock;
					printf("connected client: %d \n", clnt_sock);
				}
				else    // read message!
				{
					str_len=read(i, buf, BUF_SIZE);
					if(str_len==0)    // close request!
					{
						FD_CLR(i, &reads);
						close(i);
						printf("closed client: %d \n", i);
					}
					else
					{
						write(i, buf, str_len);    // echo!
					}
				}
			}
		}
	}
	close(serv_sock);
	return 0;
}
void error_handling(char *buf)
{
	fputs(buf, stderr);
	fputc('\n', stderr);
	exit(1);
}
