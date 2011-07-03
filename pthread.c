#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#define MAX 10
pthread_t thread[2];
pthread_mutex_t mut;
pthread_mutex_t mut_i;
int number=0,i=0;

void *thread1()
{
	printf("thread1:I'm thread 1\n");
	
	for(i=0;i<MAX;i++)
	{
		printf("thread1 : number=%d i=%d\n",number,i);
		pthread_mutex_lock(&mut);
		number++;
		pthread_mutex_unlock(&mut);
		sleep(1);
	}
	printf("thread1:main wait?\n");
	pthread_exit(NULL);
}

void *thread2()
{
	printf("thread2:I'm thread 2\n");
	for(i=0;i<MAX;i++)
	{
		printf("thread2 : number=%d i=%d\n",number,i);
		pthread_mutex_lock(&mut);
		number++;
		pthread_mutex_unlock(&mut);
		sleep(1);
	}
	printf("thread2:main wait?\n");
	pthread_exit(NULL);
}

void thread_create(void)
{
	int temp;
	memset(&thread,0,sizeof(thread));
	if((temp = pthread_create(&thread[0],NULL,thread1,NULL)) != 0)
		printf("thread1 create failed\n");
	else
		printf("thread1 create\n");

	if((temp = pthread_create(&thread[1],NULL,thread2,NULL)) != 0)
		printf("thread2 create failed\n");
	else
		printf("thread2 create\n");
}

void thread_wait()
{
	if(thread[0] != 0)
	{
		pthread_join(thread[0],NULL);
		printf("thread1 is over\n");
	}
	
	if(thread[1] != 0)
	{
		pthread_join(thread[1],NULL);
		printf("thread2 is over\n");
	}
}

int main()
{
	pthread_mutex_init(&mut,NULL);
	pthread_mutex_init(&mut_i,NULL);
	printf("main function,create thread\n");
	thread_create();
	printf("main function,wait thread over\n");
	thread_wait();
	return 0;
}
