#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define TRUE 1
#define FALSE 0
void error_handling(char *message); //에러 처리를 위한 함수선언

int main(int argc, char *argv[])
{
	int serv_sock, clnt_sock; // 서버 소켓과 클라이언트 소켓 변수
	char message[30]; // 메시지 저장 배열 크기
	int option, str_len; // 옵션 및 문자열 저장 변수
	socklen_t optlen, clnt_adr_sz;
	struct sockaddr_in serv_adr, clnt_adr;

	if(argc!=2) {  // 프로그램 인자 개수 확인
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);  // 인자가부족하면 프로그램 종료
	}

	serv_sock=socket(PF_INET, SOCK_STREAM, 0);  // 서버소켓 생성
	if(serv_sock==-1)
		error_handling("socket() error"); // 소켓 생성 오류 처리
	
	optlen=sizeof(option);
	option=TRUE;	
	setsockopt(serv_sock, SOL_SOCKET, SO_REUSEADDR, &option, optlen);
	

	memset(&serv_adr, 0, sizeof(serv_adr)); // 서버 주소 구조체 초기화
	serv_adr.sin_family=AF_INET; // 주소 체계를 IPv4로 설정 
	serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);// 모든 IP 주소에서 접속 허용
	serv_adr.sin_port=htons(atoi(argv[1])); // 포트 번호 설정

	if(bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)))
		error_handling("bind() error ");
	
	if(listen(serv_sock, 5)==-1)
		error_handling("listen error");
	clnt_adr_sz=sizeof(clnt_adr);    
	clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_adr,&clnt_adr_sz);

	while((str_len=read(clnt_sock,message, sizeof(message)))!= 0)
	{
		write(clnt_sock, message, str_len); // 클라이언트에게 메시지 전송(에코)
		write(1, message, str_len);
	}
	close(clnt_sock);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
