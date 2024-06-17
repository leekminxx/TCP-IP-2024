/* 17행에서 출력한 파일 디스크립터의 값과 22행에서 출력한 파일 디스크립터의 값의 일치
	 => fileno 함수 호출을 통해 파일 디스크립터로 적절히 변환되었음을 알 수 있음  */
#include <stdio.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
	FILE *fp;
	int fd=open("data.dat", O_WRONLY|O_CREAT|O_TRUNC);
	if(fd == -1)
	{
		fputs("file open error", stdout);
		return -1;
	}

	// 파일 디스크립터 fd 정수 값 출력
	printf("First file descriptor : %d\n", fd);
	// fdopen 함수 호출을 통해 파일 디스크립터를 FILE 포인터로 변환
	fp = fdopen(fd, "w");
	fputs("TCP/IP SOCKET PROGRAMMING\n", fp);
	// fileno 함수 호출을 통해 FILE 포인터를 파일 디스크립터로 변환 및 출력
	printf("Second file descriptor : %d\n", fileno(fp));
	fclose(fp);
	return 0;
}
