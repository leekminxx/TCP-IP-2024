#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
void* thread_main(void *arg);

int main(int argc, char* argv[])
{
	pthread_t t_id;
	int thread_param = 5;

	// thread_main 함수의 호출을 시작으로
	// 별도의 실행흐름을 구성하는 쓰레드 생성 요청
	// thread_main 호출 시 인자로 thread_param 주소 값 전달
	if(pthread_create(&t_id, NULL, thread_main, (void*)&thread_param) != 0)
	{
		puts("pthread_create() error");
		return -1;
	};

	// main 함수 실행 10초간 중지, 프로세스의 종료시기 늦추기 위해!
	sleep(10);
	puts("end of main");
	return 0;	// 실행되면 프로세스 종료!
	// 프로세스의 종료는 그 안에서 생성된 쓰레드의 종료로 이어짐
	// 쓰레드의 실행 보장을 위해 sleep(10) 삽입
	// main 함수 종료되면 쓰레드도 종료되니까 그거 방지하려고 sleep(10)
}

// 매개변수 arg로 전달되는 것은 14행에서 호출한 pthread_create 함수의 네 번째 전달 인자
void* thread_main(void *arg)
{
	int i;
	int cnt = *((int*)arg);
	for(i = 0; i < cnt; i++)
	{
		sleep(1);
		puts("running thread");
	}
	return NULL;
}
