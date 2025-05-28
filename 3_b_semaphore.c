#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

#define SIZE 3

int buffer[SIZE];
int in = 0, out = 0, item = 0;
sem_t empty, full, mutex;

void produce(){
    if(sem_trywait(&empty) !=0){
        printf("Buffer is full");
        return;
    }
    sem_wait(&mutex);
    item++;
    buffer[in] = item;
    printf("Produced: %d\n", item);
    in = (int+1) % SIZE;
    sem_post(&mutex);
    sem_post(&full);
}

void consume(){
    if(sem_trywait(&full) !=0){
        printf("Buffer is full!");
        return;
    }

    sem_wait(&mutex);
    int consumed_item = buffer[out];
    printf("Consumed: %d\n", consumed_item);
    out = (out+1) % SIZE;
    sem_post(&mutex);
    sem_post(&empty);
}

int main(){
    int choice;
    sem_init(&empty, 0, SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    while(1){
        printf("\n1. Producer\n2. Consumer\n3. Exit\nEnter your choice:");
        scanf("%d", &choice);

        switch(choice){
            case 1: produce(); break;
            case 2: consum(); break;
            case 3: 
                sem_destroy(&empty);
                sem_destroy(&full);
                sem_destroy(&mutex);
                exit(0);
        }
    }
    return 0;
}