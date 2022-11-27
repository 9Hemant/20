#include <pthread.h> 
#include <semaphore.h> 
#include <stdlib.h> 
#include <stdio.h> 
#define MaxItems 5 
#define BufferSize 5 
sem_t empty;  
sem_t full;  
int in = 0;  
int out = 0;  
int buffer[BufferSize];  
pthread_mutex_t mutex;  
void *producer(void *pno)  
{  
 int item;  
 for(int i = 0; i < MaxItems; i++)  
 {  
 item = rand();  
 sem_wait(&empty);  
 pthread_mutex_lock(&mutex);  
 buffer[in] = item;  
 printf("\nProducer %d: Insert Item %d at %d\n", *((int *)pno),buffer[in],in);  
 for (int j=0;j<5;j++)  
 printf("%d ",buffer[j]);  
 in = (in+1)%BufferSize;  
 pthread_mutex_unlock(&mutex);  
 sem_post(&full);  
 }  
  
}  
void *consumer(void *cno)  
{  
 for(int i = 0; i < MaxItems; i++)  
 {  
 sem_wait(&full);  
 pthread_mutex_lock(&mutex);  
 int item = buffer[out];  
 printf("\nConsumer %d: Remove Item %d from %d\n",*((int *)cno),item,  out); 
 for (int j=0;j<5;j++)  
 printf("%d ",buffer[j]);  
 out = (out+1)%BufferSize;  
 pthread_mutex_unlock(&mutex);  
 sem_post(&empty);  
 }  
}  
int main()  
{  
 pthread_t pro[3],con[2];  
 pthread_mutex_init(&mutex, NULL);  
 sem_init(&empty,0,BufferSize);  
 sem_init(&full,0,0);  
 int a[5] = {1,2,3,4,5};  
 for(int i = 0; i < 3; i++)  
 {  
 pthread_create(&pro[i], NULL, (void *)producer, (void *)&a[i]);   }  
 for(int i = 0; i < 2; i++)  
 {  
 pthread_create(&con[i], NULL, (void *)consumer, (void *)&a[i]);   }  
 for(int i = 0; i < 3; i++)  
 {  
 pthread_join(pro[i], NULL);  
 }  
 for(int i = 0; i < 2; i++)  
 {  
 pthread_join(con[i], NULL);  
 }  
 pthread_mutex_destroy(&mutex);  
 sem_destroy(&empty);  
 sem_destroy(&full);  
 return 0;  
}  