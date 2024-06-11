#include <stdio.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
	//각각 2바이트 , 4바이트 데이터를 변수에 저장하고 있음
	unsigned short host_port=0x1234; 
	unsigned short net_port;
	unsigned long host_addr=0x12345678;
	unsigned long net_addr;

	// 변수 host_port와 host_addr에 저장된 데이터를 네트워크 바이트 순서로 변환하고 있음
	net_port=htons(host_port);
	net_addr=htonl(host_addr);

	printf("Host ordered port: %#x \n", host_port);
	printf("Network ordered port : %#x \n", net_port);
	printf("Host ordered address : %#1x \n", host_addr);
	printf("Network ordered address : %#x \n", net_addr);
	return 0;
}

	
