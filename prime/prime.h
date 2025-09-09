#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <time.h>
#include <windows.h>

typedef struct CONFIG {
    uint64_t    MAX_INT_VAL;
    int         thread_count;
} CONFIG;

typedef struct PRIME_THREAD {
    pthread_t   thread;
    int         id;
    int         lower_bound;
    int         upper_bound;
} PRIME_THREAD;

CONFIG read_file() {
    CONFIG config_data; 
    uint64_t value = 0;
    int count = 0;

    FILE *fptr;
    fptr = fopen("config.txt", "r");

    fscanf(fptr, "%llu",&value);
    fscanf(fptr, "%d", &count);

    config_data.MAX_INT_VAL = value;
    //int *primes = calloc((value + 1), sizeof(int));

    config_data.thread_count = count;

    return config_data;
}

void *prime_thread(void *arg) {
    PRIME_THREAD *pt = (PRIME_THREAD *)arg;
    int id = pt->id, lower_bound = pt->lower_bound, upper_bound = pt->upper_bound;

    for (int num = lower_bound; num <= upper_bound; num++) {
        if (num < 2) continue; 

        int is_prime = 1;
        for (int check = 2; check <= sqrt(num); check++) {
            if (num % check == 0) {
                is_prime = 0;
                break;
            }
        }

        if (is_prime) {
            printf("Thread %d: %d is prime.\n", id, num);
        }
        Sleep(10 * id);
    }

    return NULL;
}