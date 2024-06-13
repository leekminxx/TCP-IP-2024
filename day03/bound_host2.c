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
	char msg1[] = "Hi!";  // 첫 번째 메시지
	char msg2[] = "I'm another UDP host!";  // 두 번째 메시지
	char msg3[] = "Nice to meet you";  // 세 번째 메시지

	struct sockaddr_in your_adr;  // 상대방 소켓 주소 구조체
	socklen_t your_adr_sz;  // 상대방 주소 길이를 저장할 변수

	if(argc != 3){  // 프로그램 인자가 3개가 아닐 경우
		printf("Usage : %s <IP> <port>\n", argv[0]);  // 사용법 출력
		exit(1);  // 프로그램 종료
	}
	
	sock = socket(PF_INET, SOCK_DGRAM, 0);  // UDP 소켓 생성
	if(sock == -1)  // 소켓 생성 실패 시
		error_handling("socket() error");  // 에러 핸들링
	
	memset(&your_adr, 0, sizeof(your_adr));  // 상대방 소켓 주소 구조체를 0으로 초기화
	your_adr.sin_family = AF_INET;  // 주소 체계를 IPv4로 설정
	your_adr.sin_addr.s_addr = inet_addr(argv[1]);  // 입력받은 IP 주소로 설정
	your_adr.sin_port = htons(atoi(argv[2]));  // 입력받은 포트 번호로 설정
	
	
	sendto(sock, msg1, sizeof(msg1), 0, 
					(struct sockaddr*)&your_adr, sizeof(your_adr));
	
	sendto(sock, msg2, sizeof(msg2), 0, 
					(struct sockaddr*)&your_adr, sizeof(your_adr));
	
	sendto(sock, msg3, sizeof(msg3), 0, 
					(struct sockaddr*)&your_adr, sizeof(your_adr));
	
	close(sock);  // 소켓 종료
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);  // 에러 메시지 출력
	fputc('\n', stderr);  // 개행 문자 출력
	exit(1);  // 프로그램 종료
}
