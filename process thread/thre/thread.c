/*thread_example.c */
#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#define MAX 20
pthread_t thread[4];

sem_t sem;
pthread_mutex_t mut;
int number=0, i;
char Buf[20][100] = {0};

void *thread1()
{
		int num = 0;
		char str[10] = {0};
		int fd = 0;
		char buf[100] = {0};
		
		while(1) {
			pthread_mutex_lock(&mut);            
			number++;
			num = number;                                
			pthread_mutex_unlock(&mut);
			if (number > 10)
				break;
			sprintf(str, "%d.txt", num);
			fd = open(str, O_RDONLY);
			read(fd, buf, sizeof(buf));
			strncpy(Buf[num], buf, strlen(buf));
			printf("%s\n", buf);
//			puts(buf);
			close(fd);
sem_post(&sem);
		}
		pthread_exit(NULL);		
}


void *thread2()
{ 
		int num = 0;
		char str[10] = {0};
		int fd = 0;
		char buf[100] = {0};
		
		while(1) {
			pthread_mutex_lock(&mut);            
			number++;
			num = number;                                
			pthread_mutex_unlock(&mut);
			if (number > 10)
				break;
			sprintf(str, "%d.txt", num);
			fd = open(str, O_RDONLY);
			read(fd, buf, sizeof(buf));
			strncpy(Buf[num], buf, strlen(buf));
			printf("%s\n", buf);
//			puts(buf);
			close(fd);
sem_post(&sem);
		}
		pthread_exit(NULL);
}

void *thread3()
{ 
		int num = 0;
		char str[10] = {0};
		int fd = 0;
		char buf[100] = {0};
		
		while(1) {
			pthread_mutex_lock(&mut);            
			number++;
			num = number;                                
			pthread_mutex_unlock(&mut);
			if (number > 10)
				break;
			sprintf(str, "%d.txt", num);
			fd = open(str, O_RDONLY);
			read(fd, buf, sizeof(buf));
			strncpy(Buf[num], buf, strlen(buf));
			printf("%s\n", buf);
//			puts(buf);
			close(fd);
sem_post(&sem);
		}
		pthread_exit(NULL);
}


void *thread4()
{ 
//		int num = 0;
//		char str[10] = {0};

//		char buf[100] = {0};
		int fd = 0;
		int j = 1;

		fd = open("11.txt", O_RDWR);
		
		while(1) {
			sem_wait(&sem);
			
			write(fd, Buf[j], strlen(Buf[j]));
			j++;




		}
		pthread_exit(NULL);
}


void thread_create(void)
{
        int temp;
        memset(&thread, 0, sizeof(thread));
          //comment1        /*创建线程*/
        if((temp = pthread_create(&thread[0], NULL, thread1, NULL)) != 0)       //comment2
                printf("线程1创建失败!\n");
        else
                printf("线程1被创建\n");

//sleep(1);
        if((temp = pthread_create(&thread[1], NULL, thread2, NULL)) != 0)  //comment3
                printf("线程2创建失败");
        else
                printf("线程2被创建\n");

        if((temp = pthread_create(&thread[2], NULL, thread3, NULL)) != 0)  //comment3
                printf("线程2创建失败");
        else
                printf("线程2被创建\n");

        if((temp = pthread_create(&thread[3], NULL, thread4, NULL)) != 0)  //comment3
                printf("线程2创建失败");
        else
                printf("线程2被创建\n");



}

void thread_wait(void)
{
        /*等待线程结束*/
        if(thread[0] !=0)
		{
                   //comment4
                pthread_join(thread[0],NULL);
                printf("线程1已经结束\n");

		}        
		if(thread[1] !=0)
		{                
                pthread_join(thread[1],NULL);
                printf("线程2已经结束\n");

        }
}

int main()
{        
		/*用默认属性初始化互斥锁*/
        pthread_mutex_init(&mut,NULL);
        printf("主函数，正在创建线程\n");
        thread_create();
        printf("主函数，正在等待线程完成任务\n");
        thread_wait();
        return 0;
}
