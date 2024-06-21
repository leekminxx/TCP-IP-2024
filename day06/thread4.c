/* 총 100개의 쓰레드 생성
	 반은 thread_inc를 쓰레드의 main 함수로,
	 반은 thread_des를 쓰레드의 main 함수로 호출
	 전역변수 num에 저장된 값의 증가와 감소의 최종결과로 변수 num에는
	 0 이 저장되어야 하지만 실행 결과는 0이 아님!
	 실행할 때마다 실행 결과가 다름

	 임계영역
	 - 함수 내에 둘 이상의 쓰레드가 동시에 실행하면 문제를 일으키는
	   하나 이상의 문장으로 묶여있는 코드블록!
	 - 일반적으로 임계영역은 쓰레드에 의해 실행되는 함수 내에 존재

	 쓰레드 1이 thread_inc 함수의 num+=1 실행할 때,
	 동시에 쓰레드 2가 thread_des 함수의 num-=1을 실행하는 상황!
	 이렇듯 임계영역은 서로 다른 두 문장이 각각 다른 쓰레드에 의해
	 동시에 실행되는 상황에서도 만들어질 수 있다.
	 (두 문장이 동일한 메모리 공간에 접근한다면)
	 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#define NUM_THREAD 100

void* thread_inc(void* arg);
void* thread_des(void* arg);
long long num  = 0;		// long long 형은 64비트 정수 자료형
// num은 임계영역 아님! 그냥 메모리 할당을 요구하는 변수의 선언일 뿐

int main(int argc, char* argv[])
{
	pthread_t thread_id[NUM_THREAD];
	int i;

	printf("sizeof long long : %d\n", sizeof(long long));	// long long 크기 확인
	for(i = 0; i < NUM_THREAD; i++)
	{
		if(i%2)
			pthread_create(&(thread_id[i]), NULL, thread_inc, NULL);
		else
			pthread_create(&(thread_id[i]), NULL, thread_des, NULL);
	}

	for(i = 0; i < NUM_THREAD; i++)
		pthread_join(thread_id[i], NULL);

	printf("result : %lld\n", num);
	return 0;
}

void* thread_inc(void *arg)
{
	int i;
	for(i = 0; i <50000000; i++)
		num += 1;		// 임계영역
	return NULL;
}

void* thread_des(void *arg)
{
	int i;
	for(i = 0; i < 50000000; i++)
		num -= 1;		// 임계영역
	return NULL;
}
