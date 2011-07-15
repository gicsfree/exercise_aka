/*thread_example.c */
#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>
#define MAX 20
pthread_t thread[2];
pthread_mutex_t mut;
int number=0, i;
int flag = 0;

void *thread1()
{
        printf ("thread1 : I'm thread 1\n");

// flag = 1;

        for (i = 0; i < MAX; i++)
        {  

pthread_mutex_lock(&mut);             
	printf("thread1 : number = %d\n",number); 
                
                number++;
                
                
pthread_mutex_unlock(&mut);
//sleep(3);
        }  
      
printf("thread1 :主函数在等待吗？\n");
pthread_exit(NULL);
}


void *thread2()
{ 
      
printf("thread2 : I'm thread 2\n");
// flag = 0;


        for (i = 0; i < MAX; i++)
        {  

pthread_mutex_lock(&mut);              
    printf("thread2 : number = %d\n",number);            

number++;


pthread_mutex_unlock(&mut);  
//sleep(3);
        } 
     
printf("thread2 :主函数在等待吗？\n");        
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
}

void thread_wait(void)
{
        /*等待线程结束*/
        if(thread[0] !=0)
 {
                   //comment4
                pthread_join(thread[0],NULL);
                printf("线程1已经结束\n");
// flag = 1;
        }        
if(thread[1] !=0)
 {                //comment5
                pthread_join(thread[1],NULL);
                printf("线程2已经结束\n");
// flag = 0;
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
