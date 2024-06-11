#include <stdio.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
	char *addr1="1.2.3.4";
	//1바이트당 표현할 수 있는 최대 크기의 정수는 255이므로 이는 분명 잘못된 IP주소이다. 
	//이 잘못된 주소를 이용해서 inet_addr 함수의 오류 검출능력을 확인하고자 하였다.
	char *addr2="1.2.3.256";

	// 실행결과를 통해서 9행의 함수호출은 정상적인 결과로 이어지지만, 15행의 함수호출은
	// 정상적인 결고로 이어지지 않음을 확인해야함 
	unsigned long conv_addr=inet_addr(addr1);
	if(conv_addr==INADDR_NONE)
		printf("Error occured! \n");
	else
		printf("Network ordered interger addr: %#1x \n", conv_addr);

	conv_addr=inet_addr(addr2);
	if(conv_addr==INADDR_NONE)
		printf("Error occureded \n");
	else
		printf("Network ordered integer addr: %#1x \n\n", conv_addr);
	return 0;
}


