#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <semaphore.h>

#define FILE_NAME "out.text"

pthread_mutex_t mut_num;
pthread_mutex_t mut_file;

sem_t sem;


int number=1;
int i=1;

void read_data1(void)
{
	int fd,fd2;
	char name[10];
	char buf[100];
	size_t size=0;
	int j=0;
	while(1)
	{
		pthread_mutex_lock(&mut_num);
		if(number > 10)
		{
			pthread_mutex_unlock(&mut_num);
			break;
		}
		sprintf(name,"%d.text",number);
		j=number;
		number++;
		pthread_mutex_unlock(&mut_num);

		sem_wait(&sem);
		fd=open(name,O_RDONLY);
		if(fd < 0)
		{
			printf("Open file failed\n");
			break;
		}
		size=read(fd,buf,100);
		if(size == 0)
		{
			printf("Read file failed\n");
			break;
		}
		close(fd);
		sem_post(&sem);

write:		pthread_mutex_lock(&mut_file);
		if(j == i)
		{
			fd2 = open(FILE_NAME,O_RDWR|O_CREAT|O_APPEND,0666);
			write(fd2,buf,size);
			close(fd2);
			write(1,buf,size);
			i++;
			pthread_mutex_unlock(&mut_file);
		}
		else
		{
			pthread_mutex_unlock(&mut_file);
			sleep(1);
			goto write;
		}
	}
}
void read_data2(void)
{
	int fd,fd2;
	char name[10];
	char buf[100];
	size_t size=0;
	int j=0;
	while(1)
	{
		pthread_mutex_lock(&mut_num);
		if(number > 10)
		{
			pthread_mutex_unlock(&mut_num);
			break;
		}
		sprintf(name,"%d.text",number);
		j=number;
		number++;
		pthread_mutex_unlock(&mut_num);

		sem_wait(&sem);
		fd=open(name,O_RDONLY);
		if(fd < 0)
		{
			printf("Open file failed\n");
			break;
		}
		size=read(fd,buf,100);
		if(size == 0)
		{
			printf("Read file failed\n");
			break;
		}
		close(fd);
		sem_post(&sem);

write:		pthread_mutex_lock(&mut_file);
		if(j == i)
		{
			fd2 = open(FILE_NAME,O_RDWR|O_CREAT|O_APPEND,0666);
			write(fd2,buf,size);
			close(fd2);
			write(1,buf,size);
			i++;
			pthread_mutex_unlock(&mut_file);
		}
		else
		{
			pthread_mutex_unlock(&mut_file);
			sleep(1);
			goto write;
		}
	}
}
void read_data3(void)
{
	int fd,fd2;
	char name[10];
	char buf[100];
	size_t size=0;
	int j;
	while(1)
	{
		pthread_mutex_lock(&mut_num);
		if(number > 10)
		{
			pthread_mutex_unlock(&mut_num);
			break;
		}
		sprintf(name,"%d.text",number);
		j = number;
		number++;
		pthread_mutex_unlock(&mut_num);

		sem_wait(&sem);
		fd=open(name,O_RDONLY);
		if(fd < 0)
		{
			printf("Open file failed\n");
			break;
		}
		size=read(fd,buf,100);
		if(size == 0)
		{
			printf("Read file failed\n");
			break;
		}
		close(fd);
		sem_post(&sem);

write:		pthread_mutex_lock(&mut_file);
		if(j == i)
		{
			fd2 = open(FILE_NAME,O_RDWR|O_CREAT|O_APPEND,0666);
			write(fd2,buf,size);
			close(fd2);
			write(1,buf,size);
			i++;
			pthread_mutex_unlock(&mut_file);
		}
		else
		{
			pthread_mutex_unlock(&mut_file);
			sleep(1);
			goto write;
		}
	}
}
int main()
{
	pthread_t tid1,tid2,tid3;

	pthread_mutex_init(&mut_num,NULL);
	pthread_mutex_init(&mut_file,NULL);

	sem_init(&sem,0,2);

	pthread_create(&tid1,NULL,(void *)read_data1,NULL);
	pthread_create(&tid2,NULL,(void *)read_data2,NULL);
	pthread_create(&tid2,NULL,(void *)read_data3,NULL);

	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	pthread_join(tid3,NULL);
}
