        #include <stdio.h>
        #include <unistd.h>
        #include <semaphore.h>
        #include <pthread.h>
        #define MAXSTACK 100
        int stack[MAXSTACK][2];
        int size=0;
        sem_t sem;
        
        void ReadData1(void){
        FILE *fp=fopen("1.dat","r");
        while(!feof(fp)){
        fscanf(fp,"%d %d",&stack[size][0],&stack[size][1]);
		printf("%d %d\n",stack[size][0],stack[size][1]);
        sem_post(&sem);
        ++size;
		printf(" ReadData1 :%d\n", size);
        }
        fclose(fp);
        }
        
        void ReadData2(void){
        FILE *fp=fopen("2.dat","r");
        while(!feof(fp)){
        fscanf(fp,"%d %d",&stack[size][0],&stack[size][1]);
		printf("%d %d\n",stack[size][0],stack[size][1]);
        sem_post(&sem);
        ++size;
		printf(" ReadData2 :%d\n", size);
        }
        fclose(fp);
        }
        
        void HandleData1(void){
        while(1){
        sem_wait(&sem);
		--size;
		printf(" HandleData1 :%d\n", size);
        printf("Plus:%d+%d=%d\n",stack[size][0],stack[size][1],
        stack[size][0]+stack[size][1]);
  //      --size;
        }
        }
      
void 
        HandleData2(void){
        while(1){
        sem_wait(&sem);
		--size;
		printf(" HandleData2 :%d\n", size);
        printf("Multiply:%d*%d=%d\n",stack[size][0],stack[size][1],
        stack[size][0]*stack[size][1]);
 //       --size;
        }
        }
        int main(void){
        pthread_t t1,t2,t3,t4;
        sem_init(&sem,0,0);
        pthread_create(&t1,NULL,(void *)HandleData1,NULL);
        pthread_create(&t2,NULL,(void *)HandleData2,NULL);
        pthread_create(&t3,NULL,(void *)ReadData1,NULL);
        pthread_create(&t4,NULL,(void *)ReadData2,NULL);
        
        pthread_join(t1,NULL);
        return 0;
        }
