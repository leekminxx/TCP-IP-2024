#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

void *read(void *arg);
void *accu(void *arg);
static sem_t sem_one;
static sem_t sem_two;
static int num;

int main(int argc, char* argv[])
{
	pthread_t id_t1, id_t2;
	// 2개의 세마포어 생성
	sem_init(&sem_one, 0, 0);		// 세마포어 값이 0
	sem_init(&sem_two, 0, 1);		// 세마포어 값이 1

	pthread_create(&id_t1, NULL, read, NULL);
	pthread_create(&id_t2, NULL, accu, NULL);

	pthread_join(id_t1, NULL);
	pthread_join(id_t2, NULL);

	sem_destroy(&sem_one);
	sem_destroy(&sem_two);
	return 0;
}

void *read(void *arg)
{
	int i;
	for(i = 0; i < 5; i++)
	{
		fputs("Input num : ", stdout);

		// 세마포어 변수 sem_two를 이용한 wait 함수 호출
		// accu 함수를 호출하는 쓰레드가 값을 가져가지도 않았는데
		// read 함수를 호출하는 쓰레드가 값을 다시 가져다놓는(이전 값 덮어써버리는) 상황 방지용
		sem_wait(&sem_two);
		scanf("%d", &num);
		// 세마포어 변수 sem_one을 이용한 post 함수 호출
		sem_post(&sem_one);
	}
	return NULL;
}

void *accu(void *arg)
{
	int sum = 0, i;
	for(i = 0; i < 5; i++)
	{
		// 세마포어 변수 sem_one을 이용한 wait 함수 호출
		// read 함수를 호출하는 쓰레드가 새로운 값을 가져다 놓기도 전에
		// accu 함수가 값을 가져가 버리는(이전 값을 다시 가져가는) 상황 방지용
		sem_wait(&sem_one);
		sum += num;
		// 세마포어 변수 sem_two를 이용한 post 함수 호출
		sem_post(&sem_two);
	}
	printf("Result : %d\n", sum);
	return NULL;
}
