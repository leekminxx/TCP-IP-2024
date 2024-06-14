#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	int status;
	pid_t pid=fork(); // 첫번째 자식 프로세스 생성
	if(pid==0)  // 첫 번째 자식 프로세스
	{
		return 3;  // 첫 번째 자식은 3을 반환
	}
	else
	{
		printf("Child PID: %d \n", pid);  //첫 번째 자식의 PID 출력
		pid=fork(); // 두 번째 자식 프로세스 생성
		if(pid==0)  // 두 번째 자식 프로세스
		{
			exit(7); // 7인 상태로 종료
		}
		else  // 여전히 부모 상태일때
		{
			printf("Child PID: %d \n", pid);  // 두 번째 자식의 PID 출력
			wait(&status); // 첫 번째 자식이 종료될 때까지 대기
			if(WIFEXITED(status)) // 첫 번째 자식이 정상 종료되었는지 확인
				printf("Child send one: %d \n", WEXITSTATUS(status)); //첫 번째 자식의 종료상태를 출력

			wait(&status);
			if(WIFEXITED(status))
				printf("Child send two: %d \n", WEXITSTATUS(status));
			sleep(30);     // Sleep 30 sec.
		}
	}
	return 0;
}
