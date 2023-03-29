/*
    Written by Dausen Mason      CWID: 11955307
    CS301 Spring 2023
    Project 3
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include "mytime.h"

volatile int done = 0;

struct lunch {
    int custCount;
    int serverCount;
    int currentTicket;
    int nextTicket;

    sem_t customers;
    sem_t servers;
    sem_t server_count;
    pthread_mutex_t mutex;

    int servedCount;
};

void nowServing(int ticket){
    printf("Serving %d\n", ticket);

    return;
}

void lunch_init(struct lunch *lunch) {
    lunch->custCount = 0;
    lunch->serverCount = 0;
    lunch->currentTicket = 0;
    lunch->nextTicket = 1;

    sem_init(&lunch->customers, 0, 0);
    sem_init(&lunch->servers, 0, 0);
    sem_init(&lunch->server_count, 0, 0);
    pthread_mutex_init(&lunch->mutex, NULL);

    lunch->servedCount = 0;
}

int lunch_get_ticket(struct lunch *lunch) {
    printf("%ld enter lunch_get_ticket\n", pthread_self());

    int t = mytime (0, 5);

    pthread_mutex_lock(&lunch->mutex);

    sleep(t);

    int ticket = lunch->nextTicket;
    lunch->nextTicket++;
    lunch->custCount++;

    pthread_mutex_unlock(&lunch->mutex);

    printf("%ld get ticket %d\n", pthread_self(), ticket);
    printf("%ld leave lunch_get_ticket\n", pthread_self());

    sem_post(&lunch->customers);

    return ticket;
}


void lunch_wait_turn(struct lunch *lunch, int ticket) {
    printf("%ld enter lunch_wait_turn with %d\n", pthread_self(), ticket); 
    sem_wait(&lunch->servers);
    printf("%ld leave lunch_wait_turn after ticket %d\n", pthread_self(), ticket);
}

void lunch_wait_customer(struct lunch *lunch) {
    printf("%ld enter lunch_wait_customer\n", pthread_self());

    int t = mytime(5, 15);

    printf("Sleeping Time: %d sec; Thread Id = %ld\n", t, pthread_self());

    sleep(t);

    sem_wait(&lunch->customers);
    pthread_mutex_lock(&lunch->mutex);

    int ticket = lunch->currentTicket + 1;

    lunch->currentTicket++;
    lunch->custCount--;
    lunch->servedCount++;

    nowServing(ticket);

    pthread_mutex_unlock(&lunch->mutex);
    sem_post(&lunch->servers);
    sem_post(&lunch->server_count);

    printf("%ld after served ticket %d\n", pthread_self(), ticket);
    printf("%ld leave lunch_wait_customer\n", pthread_self());
    
}

void *customer_thread(void *cust) {
    struct lunch *lunch = (struct lunch *)cust;

    int ticket = lunch_get_ticket(lunch);
    lunch_wait_turn(lunch, ticket);

    return NULL;
}


void *server_thread(void *serv) {
    struct lunch *lunch = (struct lunch *)serv;
    sem_post(&lunch->server_count);
    while (1) {
        sem_wait(&lunch->server_count); //Wait for a free server
        if(done){
            break;
        }
        lunch_wait_customer(lunch);
    }
    sem_post(&lunch->server_count);
    
    return NULL;
}


int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Error: not enough arguments\n");
        return 0;
    }

    int i;

    int servers = atoi(argv[1]);
    int customers = atoi(argv[2]);

    if (customers < 1 || servers < 1) {
        printf("Error: customers and servers must both be greater than 1.\n");
        return 0;
    }
    struct lunch lunch;
    lunch_init(&lunch);

    //Create customer threads
    pthread_t custThreads[customers];
    for (i = 0; i < customers; i++) {
        pthread_create(&custThreads[i], NULL, customer_thread, &lunch);
    }

    //Create server threads
    pthread_t serverThreads[servers];
    for (i = 0; i < servers; i++) {
        pthread_create(&serverThreads[i], NULL, server_thread, &lunch);
    }

    //Join customer threads
    for (i = 0; i < customers; i++) {
        pthread_join(custThreads[i], NULL);
    }

    //Wait for all customers to be served
    while (lunch.servedCount < customers){
        sleep(1);
    }
    //Set done = 1 so that the program can exit
    done = 1;

    printf("joining server threads\n");

    //Join server threads
    for (i = 0; i < servers; i++) {
        printf("Top for: i = %d\n", i);
        pthread_join(serverThreads[i], NULL);
    }

    return 0;
}