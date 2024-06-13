#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30
void error_handling(char *message);

int main(int argc, char *argv[])
{
	int sd;
	FILE *fp;
	
	char buf[BUF_SIZE];
	int read_cnt;
	struct sockaddr_in serv_adr;  // 서버가 전송하는 파일 데이터를 담기 위해서 파일을 하나 생성하고있음
	if(argc!=3) {
		printf("Usage: %s <IP> <port>\n", argv[0]);
		exit(1);
	}
	
	fp=fopen("receive.dat", "wb");
	sd=socket(PF_INET, SOCK_STREAM, 0);   

	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family=AF_INET;  //EOF가 전송될때까지 데이터를 수신한 다음, 18행에서 생성한 파일을 담고 있음
	serv_adr.sin_addr.s_addr=inet_addr(argv[1]);
	serv_adr.sin_port=htons(atoi(argv[2]));

	connect(sd, (struct sockaddr*)&serv_adr, sizeof(serv_adr)); // 서버로 인사 메시지를 전송하고 있음 , 서버의 입력 스트림이 닫히지 않았다면 , 이메시지를 수신 할 수 없음
	
	while((read_cnt=read(sd, buf, BUF_SIZE ))!=0)
		fwrite((void*)buf, 1, read_cnt, fp);
	
	puts("Received file data");
	write(sd, "Thank you", 10);
	fclose(fp);
	close(sd);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
