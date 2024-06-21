/* Worker 쓰레드 모델
	 1 ~ 5까지 더하는 쓰레드(Worker),
	 6 ~ 10까지 더하는 쓰레드(Worker),
	 main 함수에서는 단지 연산결과 출력! */
#include <stdio.h>
#include <pthread.h>
void* thread_summation(void *arg);

// 전역변수 sum에 두 쓰레드가 접근!
int sum = 0;

int main(int argc, char* argv[])
{
	pthread_t id_t1, id_t2;
	int range1[] = {1, 5};
	int range2[] = {6, 10};

	pthread_create(&id_t1, NULL, thread_summation, (void*)range1);
	pthread_create(&id_t2, NULL, thread_summation, (void*)range2);

	pthread_join(id_t1, NULL);
	pthread_join(id_t2, NULL);
	printf("result : %d\n", sum);
	return 0;
}

void* thread_summation(void * arg)
{
	int start = ((int*)arg)[0];
	int end = ((int*)arg)[1];

	while(start <= end)
	{
		sum += start;
		start++;
	}
	return NULL;
}
