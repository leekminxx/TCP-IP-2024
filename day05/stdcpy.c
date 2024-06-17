/* fputs & fgets 함수를 이용한 파일 복사
	 버퍼링 기반의 복사가 이루어짐!
	 전송해야 할 데이터의 양이 많을 수록
	 버퍼링을 통한 데이터 전송이 성능에 도움이 됨! */
#include <stdio.h>
#define BUF_SIZE 3

int main(int argc, char *argv[])
{
		FILE * fp1;		// fp1에 저장되는 것은 FILE 구조체의 포인터
		FILE * fp2;		// fp2에 저장되는 것은 FILE 구조체의 포인터
		char buf[BUF_SIZE];

		fp1=fopen("news.txt","r");
		fp2=fopen("cpy.txt","w");

		while(fgets(buf, BUF_SIZE, fp1)!=NULL)
				fputs(buf, fp2);

		fclose(fp1);
		fclose(fp2);
		return 0;
}

