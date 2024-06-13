#include <stdio.h>       // 표준 입출력 함수 사용을 위해 포함
#include <stdlib.h>      // 표준 라이브러리 함수 사용을 위해 포함
#include <string.h>      // 문자열 처리 함수 사용을 위해 포함
#include <unistd.h>      // UNIX 표준 함수 사용을 위해 포함
#include <arpa/inet.h>   // 인터넷 프로토콜 관련 함수 사용을 위해 포함
#include <sys/socket.h>  // 소켓 함수 사용을 위해 포함

#define BUF_SIZE 30      // 버퍼 크기를 30으로 정의
void error_handling(char *message);  // 에러 핸들링 함수 선언

int main(int argc, char *argv[])
{
	int sock;  // 소켓 파일 디스크립터
	char message[BUF_SIZE];  // 메시지를 저장할 버퍼
	int str_len;  // 수신된 메시지 길이를 저장할 변수
	socklen_t adr_sz;  // 주소 길이를 저장할 변수
	
	struct sockaddr_in serv_adr, from_adr;  // 서버 주소와 송신자 주소 구조체
	if(argc != 3){  // 프로그램 인자가 3개가 아닐 경우
		printf("Usage : %s <IP> <port>\n", argv[0]);  // 사용법 출력
		exit(1);  // 프로그램 종료
	}
	
	sock = socket(PF_INET, SOCK_DGRAM, 0);  // UDP 소켓 생성
	if(sock == -1)  // 소켓 생성 실패 시
		error_handling("socket() error");  // 에러 핸들링
	
	memset(&serv_adr, 0, sizeof(serv_adr));  // 서버 주소 구조체를 0으로 초기화
	serv_adr.sin_family = AF_INET;  // 주소 체계를 IPv4로 설정
	serv_adr.sin_addr.s_addr = inet_addr(argv[1]);  // 입력받은 IP 주소로 설정
	serv_adr.sin_port = htons(atoi(argv[2]));  // 입력받은 포트 번호로 설정

	// 임시 주소 구조체 초기화 및 바인딩
	struct sockaddr_in temp_adr;  // 임시 주소 구조체
	memset(&temp_adr, 0, sizeof(temp_adr));  // 임시 주소 구조체를 0으로 초기화
	temp_adr.sin_family = AF_INET;  // 주소 체계를 IPv4로 설정
	temp_adr.sin_addr.s_addr = inet_addr("0.0.0.0");  // 모든 IP 주소에서 수신하도록 설정
	temp_adr.sin_port = htons(54192);  // 포트를 54192로 설정

	bind(sock, (struct sockaddr *)&temp_adr, sizeof(temp_adr));  // 소켓과 주소 바인딩

	while(1)
	{
		fputs("Insert message(q to quit): ", stdout);  // 메시지 입력 요청 출력
		fgets(message, sizeof(message), stdin);  // 메시지 입력 받기     
		if(!strcmp(message, "q\n") || !strcmp(message, "Q\n"))  // 입력이 'q' 또는 'Q'일 경우
			break;  // 반복 종료
		
		sendto(sock, message, strlen(message), 0, 
					(struct sockaddr*)&serv_adr, sizeof(serv_adr));  // 메시지 전송
		printf("serv_adr\n");
		printf("IP: %d PORT: %d\n", ntohl(serv_adr.sin_addr.s_addr), ntohs(serv_adr.sin_port));  // 서버 주소 정보 출력

		adr_sz = sizeof(from_adr);  // 송신자 주소 길이 설정
		str_len = recvfrom(sock, message, BUF_SIZE, 0, 
					(struct sockaddr*)&from_adr, &adr_sz);  // 메시지 수신
		printf("recvfrom\n");
		printf("IP: %d PORT: %d\n", ntohl(from_adr.sin_addr.s_addr), ntohs(from_adr.sin_port));  // 송신자 주소 정보 출력
		
		message[str_len] = 0;  // 메시지 끝에 null 문자 추가
		printf("Message from server: %s", message);  // 수신된 메시지 출력
	}	

	close(sock);  // 소켓 종료
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);  // 에러 메시지 출력
	fputc('\n', stderr);  // 개행 문자 출력
	exit(1);  // 프로그램 종료
}
