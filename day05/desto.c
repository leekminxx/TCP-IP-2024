/* sudo cat data.dat 으로 확인 */
#include <stdio.h>
#include <fcntl.h>

int main(void)
{
	FILE *fp;
	// open 함수를 통해 파일 생성 => 파일 디스크립터 반환
	int fd = open("data.dat", O_WRONLY|O_CREAT|O_TRUNC);
	if(fd == -1)
	{
		fputs("file open error", stdout);
		return -1;
	}

	// fdopen 함수를 통해 파일 디스크립터를 FILE 포인터로 변환
	// w =>  출력모드의 FILE 포인터 반환됨
	fp = fdopen(fd, "w");
	// 위에서 반환된 FILE 포인터 기반으로 표준출력 함수 fputs 함수 호출
	fputs("Network C programming\n", fp);
	// FILE 포인터를 이용한 파일 닫기
	// 파일 자체가 완전히 종료되므로 파일 디스크립터를 이용해 또 다시 종료할 필요없음!!
	// fclose 함수 호출 이부후턴 파일 디스크립터도 의미없는 정수,,
	fclose(fp);
	return 0;
}
