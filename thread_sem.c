#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#include <semaphore.h>
#include <unistd.h>
#define MAXSTACK 100
int stack[MAXSTACK][2];
int size = 0;
sem_t sem;

void read_data1(void)
{
	FILE *fp=fopen("1.dat","r");
	while(!feof(fp))
	{
		fscanf(fp,"%d %d",&stack[size][0],&stack[size][1]);
		sem_post(&sem);
		++size;
		sleep(1);
	}
	fclose(fp);
}

void read_data2(void)
{
	FILE *fp=fopen("2.dat","r");
	while(!feof(fp))
	{
		fscanf(fp,"%d %d",&stack[size][0],&stack[size][1]);
		sem_post(&sem);
		++size;
		sleep(1);
	}
	fclose(fp);
}

void handle_data1()
{
	sleep(1);
	while(1)
	{
		sleep(1);
		sem_wait(&sem);
		printf("Plus:%d+%d=%d\n",stack[size][0],stack[size][1],stack[size][0]+stack[size][1]);
		--size;
	}
}

void handle_data2()
{
	sleep(1);
	while(1)
	{
		sleep(1);
		sem_wait(&sem);
		printf("Multiply:%d*%d=%d\n",stack[size][0],stack[size][1],stack[size][0]*stack[size][1]);
		--size;
	}
}

int main()
{
	pthread_t t1,t2,t3,t4;
	sem_init(&sem,0,0);
	pthread_create(&t1,NULL,(void *)handle_data1,NULL);
	pthread_create(&t2,NULL,(void *)handle_data2,NULL);
	pthread_create(&t3,NULL,(void *)read_data1,NULL);
	pthread_create(&t4,NULL,(void *)read_data2,NULL);

	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	pthread_join(t3,NULL);
	pthread_join(t4,NULL);
}
