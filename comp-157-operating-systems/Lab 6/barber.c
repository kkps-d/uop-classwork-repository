// Number of chairs in the waiting room
// Default - 5
#define WAITING_CHAIRS 5

// Changes how long many customers in total will be served before program ends
// Default - 5
#define MAX_CUSTOMERS_SERVED 5

// Change how often customers arrive, larger number = less often
// Default - 5
#define FREQ_CUSTOMER 5

// Changes how long max a customer can take being served
// Default - 10
#define MAX_CUSTOMER_TIME 10

// GOTO customer_generator_thread():132 to enable random seed

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include "structs.h"

void *barber_thread(void *param);
void *customer_thread(void *param);
void *customer_generator_thread(void *param);

int customers_served = 0;

Customer *serving; // Customer being served
WaitQueue waiting; // Waiting room

pthread_t barber_t;
pthread_t customer_generator_t;
pthread_attr_t attr;

pthread_mutex_t waiting_mutex;
pthread_mutex_t customers_served_mutex;
pthread_mutex_t barber_mutex;
pthread_cond_t wake_barber;
pthread_cond_t finished_serving_customer;

int main()
{
    // Initialize all conditions and mutexes
    pthread_mutex_init(&waiting_mutex, NULL);
    pthread_mutex_init(&customers_served_mutex, NULL);
    pthread_mutex_init(&barber_mutex, NULL);
    pthread_cond_init(&wake_barber, NULL);
    pthread_cond_init(&finished_serving_customer, NULL);

    // Initialize waiting queue
    waiting = new_WaitQueue(WAITING_CHAIRS);

    // Create required threads, ORDER MATTERS: 1. Barber, 2. Customer Generator
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    pthread_create(&barber_t, &attr, barber_thread, NULL);
    pthread_create(&customer_generator_t, &attr, customer_generator_thread, NULL);

    // Threads to wait for: Barber, Customer Generator
    pthread_join(barber_t, NULL);
    pthread_join(customer_generator_t, NULL);

    // Exit
    printf("[  MAIN  ] <%d> customers has been served. Program terminated.\n", customers_served);
    return 0;
}

void *customer_thread(void *param)
{
    Customer *c = (Customer *)param;
    pthread_mutex_lock(&c->exec_mutex);
    while (c->elapsed != c->duration)
    {
        c->elapsed++;
        sleep(1);
        printf("[CUSTOMER][#%d] Being served by barber. Time elapsed: %d\n", c->num, c->elapsed);
    }
    pthread_mutex_unlock(&c->exec_mutex);
    pthread_cond_signal(&finished_serving_customer);
    pthread_exit(NULL);
}

void *barber_thread(void *param)
{
    while (1)
    {
        // Barber is sleeping by default
        if (waiting.num_queued == 0)
        {
            printf("[ BARBER ] Barber is now asleep...\n");
            pthread_cond_wait(&wake_barber, &barber_mutex);
            printf("[ BARBER ] Barber is now awake.\n");
        }

        // Pop a customer from queue and serve
        pthread_mutex_lock(&waiting_mutex);
        serving = WQ_pop(&waiting);
        printf("[ BARBER ] Got customer from queue.\n");
        pthread_mutex_unlock(&waiting_mutex);

        printf("[ BARBER ] Now serving customer [#%d] for <%d> long.\n", serving->num, serving->duration);
        pthread_mutex_unlock(&serving->exec_mutex); // Allows the selected customer thread to run

        // Wait for customer thread to finish executing
        pthread_cond_wait(&finished_serving_customer, &barber_mutex);
        printf("[ BARBER ] Finished serving customer [#%d].\n",serving->num);

        // If done serving customer, increment customers served
        pthread_mutex_lock(&customers_served_mutex);
        customers_served++;

        // Terminate Barber thread if MAX_CUSTOMERS_SERVED reached
        if (customers_served == MAX_CUSTOMERS_SERVED)
        {
            printf("[ BARBER ] Max customers served: <%d>, thread terminated.\n", customers_served);
            pthread_mutex_unlock(&customers_served_mutex);
            pthread_exit(NULL);
        }
        pthread_mutex_unlock(&customers_served_mutex);
    }
}

void *customer_generator_thread(void *param)
{
    int internal_customers_served = 1;

    // Uncomment next line to enable true random
    // srand(time(NULL));

    sleep(1); // wait for other threads to initialize

    while (1)
    {
        int random = rand();
        if (random % FREQ_CUSTOMER == 0)
        {
            // Customer arrived
            pthread_mutex_lock(&waiting_mutex);

            // If waiting not full...
            if (!WQ_isFull(&waiting))
            {
                int duration = 1 + random % MAX_CUSTOMER_TIME; // Generate a random time
                printf("[  CGEN  ] Customer has arrived, and will take %d time.\n", duration);
                Customer *c = new_Customer();
                c->num = internal_customers_served; // Set customer num for clarification during debugging
                internal_customers_served++;
                c->duration = duration;             // Set total duration of customer service

                // Customer's mutex is locked so that it does not execute when thread is created
                pthread_mutex_init(&c->exec_mutex, NULL);
                pthread_mutex_lock(&c->exec_mutex);
                pthread_create(&c->tid, &attr, customer_thread, c);
                WQ_push(&waiting, c); // Push customer to waiting queue

                // Wake up sleeping barber
                pthread_cond_signal(&wake_barber);
            }
            else
            {
                printf("[  CGEN  ] Customer has arrived, but waiting room was full so customer left\n");
            }
            pthread_mutex_unlock(&waiting_mutex);
        }

        pthread_mutex_lock(&customers_served_mutex);
        if (customers_served == MAX_CUSTOMERS_SERVED)
        {
            printf("[  CGEN  ] Max customers served: <%d>, thread terminated.\n", customers_served);
            pthread_mutex_unlock(&customers_served_mutex);
            pthread_exit(NULL);
        }
        pthread_mutex_unlock(&customers_served_mutex);
        sleep(1);
    }
}