#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#define BUF_SIZE 100
void error_handling(char * message);

int main(void)
{
		int fd;
		char buf[BUF_SIZE];

		fd=open("data.txt", O_RDONLY);  // 파일 data.txt를 읽기 전용으로 열고 있다.
		if(fd== -1)
			error_handling("open() error!");
		printf("file descriptor: %d \n" , fd);

		if(read(fd, buf, sizeof(buf))==-1)  // read 함수를 이용해서 11행에 선언된 배열 buf 에 읽어 들인 데이터를 저장하고 있다.
			error_handling("read() error!");
		printf("file data: %s", buf);
		close(fd);
		return 0;
}

void error_handling(char * message)
{
	// 이전 예제와 동일하므로 생략 !
}
	
