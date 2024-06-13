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
	struct sockaddr_in my_adr, your_adr;  // 소켓 주소 구조체
	socklen_t adr_sz;  // 주소 길이를 저장할 변수
	int str_len, i;  // 메시지 길이와 루프 카운터 변수

	if(argc != 2){  // 프로그램 인자가 2개가 아닐 경우
		printf("Usage : %s <port>\n", argv[0]);  // 사용법 출력
		exit(1);  // 프로그램 종료
	}
	
	sock = socket(PF_INET, SOCK_DGRAM, 0);  // UDP 소켓 생성
	if(sock == -1)  // 소켓 생성 실패 시
		error_handling("socket() error");  // 에러 핸들링
	
	memset(&my_adr, 0, sizeof(my_adr));  // 소켓 주소 구조체를 0으로 초기화
	my_adr.sin_family = AF_INET;  // 주소 체계를 IPv4로 설정
	my_adr.sin_addr.s_addr = htonl(INADDR_ANY);  // 모든 IP 주소에서 수신하도록 설정
	my_adr.sin_port = htons(atoi(argv[1]));  // 포트를 입력받은 값으로 설정
	
	if(bind(sock, (struct sockaddr*)&my_adr, sizeof(my_adr)) == -1)  // 소켓과 주소 바인딩
		error_handling("bind() error");  // 에러 핸들링
	
	for(i = 0; i < 3; i++)  // 3번 반복
	{
		sleep(5);  // 5초 대기
		adr_sz = sizeof(your_adr);  // 상대방 주소 길이 저장
		str_len = recvfrom(sock, message, BUF_SIZE, 0, 
								(struct sockaddr*)&your_adr, &adr_sz);  // 메시지 수신
		if (str_len < 0)  // 메시지 수신 실패 시
			error_handling("recvfrom() error");  // 에러 핸들링
	
		printf("Message %d: %s \n", i+1, message);  // 수신한 메시지 출력
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
