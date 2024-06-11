#include <stdio.h>

int main(int argc, char* argv[])
{
	printf("전 달 하는 인 자 갯 수: %d\n", argc);
	printf("실행파일 : %s\n", argv[0]);
	for(int i=1; i < argc; i++) {
		printf("전달인자: %s\n", argv[i]);
	}

	return 0;
}
