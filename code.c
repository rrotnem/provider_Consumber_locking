#include <stdio.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h> /* required for rand() */
#include <unistd.h>
#include "buffer.h"

//variables
long sleepTime, proNum, conNum;
int inx = 0, in = 0, out = 0;
//locks
pthread_mutex_t mutex;
sem_t full;
sem_t empty;

/* the buffer */
buffer_item buffer[BUFFER_SIZE];

//insert item
int insert_item(buffer_item item) {

    if(in < BUFFER_SIZE){
     buffer[in] = item;
     in = (in+1)%BUFFER_SIZE;
     return 0;
    }

  return -1;

}
//remove item from buffer
int remove_item(buffer_item *item) {

  if(out < BUFFER_SIZE){
      buffer[out] = *item;
      out = (out+1)%BUFFER_SIZE;
    return 0;
    }

  return -1;

}

//producer
void *producer(void *data)
{
    buffer_item item;
    int i = 0;
    while(i < 3) {
        item = rand(); // Produce an random item
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        printf("Producer %d: Insert Item %d at %d\n\n", *((int *)data),buffer[in],in);
        int insert = insert_item(item);
        if(insert < 0){
            printf("Insert error.");
        }
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
        i ++;
    }
}
void *consumer(void *data)
{
    buffer_item item;
    int i = 0;
    while(i < 3) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        printf("Consumer %d: Remove Item %d from %d\n\n",*((int *)data),item, out);
        int insert = remove_item(&item);
        if(insert < 0){
            printf("Remove error.");
        }
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        i++;
    }
}

int main(int argc, char *argv[]) {
     char *ptr, *ptr1, *ptr2;

    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, 5);
    sem_init(&full, 0, 0);
    printf("&&&&&: \nThis program starts now....\n");
    printf("Project2: \n");
    /* 1. Get command line arguments argv[1],argv[2],argv[3] */
    if( argc == 4 ) {

        printf("%s %s %s \n", argv[1], argv[2], argv[3]);
        sleepTime = strtol(argv[1], &ptr, 10);
        proNum = strtol(argv[2], &ptr1, 10);
        conNum = strtol(argv[3], &ptr1, 10);
        int a[10] = {1,2,3,4,5,6,};

        if(sleepTime > 0 && proNum > 0 && conNum > 0 ){

          pthread_t pro[proNum],con[conNum];


    int table[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9 , 10}; //track producer or consumer

    for(int i = 0; i < proNum; i++) {
        pthread_create(&pro[i], NULL, producer, (void *)&table[i]);
    }
    for(int i = 0; i < conNum; i++) {
        pthread_create(&con[i], NULL, consumer, (void *)&table[i]);
    }

    for(int i = 0; i < proNum; i++) {
        pthread_join(pro[i], NULL);
    }
    for(int i = 0; i < conNum; i++) {
        pthread_join(con[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;




        }else{
            printf("enter three arguments in numbers.");
        }


    }

  return 0;
}