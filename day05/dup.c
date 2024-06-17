#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	int cfd1, cfd2;
	char str1[] = "Hi~ \n";
	char str2[] = "It's nice day~ \n";

	// dup 함수 호출을 통한 파일 디스크립터 1 복사
	// 파일 디스크립터 1은 시스템에 의해 자동으로 열리는 표준 출력
	cfd1 = dup(1);
	// dup2 함수 호출을 통해 복사한 파일 디스크립터를 재복사
	// 정수 값도 7로 지정
	cfd2 = dup2(cfd1, 7);

	printf("fd1 = %d, fd2 = %d \n", cfd1, cfd2);
	// 복사된 파일 디스크립터를 이용한 출력
	write(cfd1, str1, sizeof(str1));
	write(cfd2, str2, sizeof(str2));

	// 복사된 파일 디스크립터를 모두 종료
	close(cfd1);
	close(cfd2);
	// 아직 파일 디스크립터 하나가 남아있는 상태이므로 출력이 여전히 이뤄짐
	write(1, str1, sizeof(str1));
	// 마지막 파일 디스크립터 종료
	close(1);
	// 아래의 출력은 이뤄지지 않음!!
	write(1, str2, sizeof(str2));
	return 0;
}
