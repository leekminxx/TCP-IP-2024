/*# date : 2024-06-14
	# file : signal.c
	# desc : 시그널 핸들링
	---------------------
시그널이 발생했을 때 호출되어야 할 함수가 각각 정의되어있음 이러하 유형을 시그널 핸들러(Handler)이라고 함
SIGALRM 시그널을 반복 발생시키기 위해 시그널 핸들러 내에서 alarm  함수를 호출
*/




#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void timeout(int sig)
{
	if(sig==SIGALRM)
		puts("Time out!");

	alarm(2);
}
void keycontrol(int sig)
{
	if(sig==SIGINT)
		puts("CTRL+C pressed");
}

int main(int argc, char *argv[])
{
	int i;
	signal(SIGALRM, timeout);
	signal(SIGINT, keycontrol);
	alarm(2);

	for(i=0; i<3; i++)
	{
		puts("wait...");
		sleep(100);
	}
	return 0;
}
