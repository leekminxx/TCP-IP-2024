/* 긴급 메시지 전송 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUF_SIZE 30
void error_handling(char *message);

int main(int argc, char *argv[])
{
	int sock;
	struct sockaddr_in recv_adr;

	if(argc!=3) {
		printf("Usage : %s <IP> <port>\n", argv[0]);
		exit(1);
	 }

	sock=socket(PF_INET, SOCK_STREAM, 0); 	//클라이언트 소켓 설정
 	memset(&recv_adr, 0, sizeof(recv_adr));
	recv_adr.sin_family=AF_INET;
	recv_adr.sin_addr.s_addr=inet_addr(argv[1]);
	recv_adr.sin_port=htons(atoi(argv[2]));

	if(connect(sock, (struct sockaddr*)&recv_adr, sizeof(recv_adr))==-1)
		error_handling("connect() error!");

	// 데이터 전송 진행
	// 일반적인 도착 순서대로라면 123, 4, 567, 890 순 전달
	// 4, 890이 긴급으로 전송되었으므로 도착 순서에 변화 생겼다고 예상 가능
	write(sock, "123", strlen("123"));
	send(sock, "4", strlen("4"), MSG_OOB);
	write(sock, "567", strlen("567"));
	send(sock, "890", strlen("890"), MSG_OOB);

	close(sock);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
