#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <time.h>
#include <windows.h>
#include <string.h>

typedef struct CONFIG {
    uint64_t    MAX_INT_VAL;
    uint64_t    thread_count;
} CONFIG;

typedef struct PRIME_THREAD {
    pthread_t   thread;
    int         id;
    uint64_t    lower_bound;
    uint64_t    upper_bound;
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

    fclose(fptr);

    return config_data;
}

void clear_file(int core_count) {
    char filename[32];
    FILE *fptr;

    for(int id = 0; id < core_count; id++) { 
        snprintf(filename, sizeof(filename), "thread_outputs/Thread_%d.txt", id);
        fptr = fopen(filename, "w");  
        if (fptr) { fclose(fptr); }
    }
}

void write_to_file(int id, int prime_no) {
    char filename[32];  

    snprintf(filename, sizeof(filename), "thread_outputs/Thread_%d.txt", id);

    FILE *fptr = fopen(filename, "a");
    if (fptr == NULL) {
        perror("Error opening file");
        return;
    }

    fprintf(fptr, "Checked: %d\n", prime_no);

    fclose(fptr);
}

void *prime_thread(void *arg) {
    PRIME_THREAD *pt = (PRIME_THREAD *)arg;
    int id = pt->id;
    uint64_t lower_bound = pt->lower_bound, upper_bound = pt->upper_bound;

    for (uint64_t num = lower_bound; num <= upper_bound; num++) {
        if (num < 2) continue; 

        int is_prime = 1;
        for (int check = 2; check <= sqrt(num); check++) {
            if (num % check == 0) {
                is_prime = 0;
                break;
            }
        }

        if (is_prime) {
            printf("Thread %d: %llu is prime.\n", id, num);
            write_to_file(id, num);
        }
        //Sleep(10 * id);
    }

    return NULL;
}