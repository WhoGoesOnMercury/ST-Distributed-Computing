#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <time.h>
#include <windows.h>
#include <string.h>
#include <inttypes.h>

typedef struct CONFIG {
    uint64_t    MAX_INT_VAL;
    int         thread_count;
    int         print_mode;   // 0 (print immediately) or 1 (wait until all is finished)
    int         division_mode; // 0 (straight division) or 1 (cooperative division)
} CONFIG;

typedef struct PRIME_THREAD {
    pthread_t   thread;
    int         id;
    uint64_t    lower_bound;
    uint64_t    upper_bound;
} PRIME_THREAD;

typedef struct RESULT {
    int thread_id;
    uint64_t prime;
    char timestamp[32];
} RESULT;

/*
    Global variables
*/
CONFIG config;
RESULT *results = NULL;
size_t result_count = 0;
pthread_mutex_t result_lock = PTHREAD_MUTEX_INITIALIZER;

CONFIG read_file() {
    CONFIG config_data; 
    uint64_t value = 0;
    int count = 0, print_mode = 0, division_mode = 0;

    FILE *fptr = fopen("config.txt", "r");
    if (!fptr) {
        perror("Error opening config.txt");
        exit(1);
    }

    if (fscanf(fptr, "%llu", &value) != 1) {
        fprintf(stderr, "Invalid MAX_INT_VAL in config.txt\n");
        exit(1);
    }
    if (fscanf(fptr, "%d", &count) != 1) {
        fprintf(stderr, "Invalid thread_count in config.txt\n");
        exit(1);
    }
    if (fscanf(fptr, "%d", &print_mode) != 1) {
        fprintf(stderr, "Invalid print_mode in config.txt\n");
        exit(1);
    }
    if (fscanf(fptr, "%d", &division_mode) != 1) {
        fprintf(stderr, "Invalid division_mode in config.txt\n");
        exit(1);
    }

    fclose(fptr);

    config_data.MAX_INT_VAL = value;
    config_data.thread_count = count;
    config_data.print_mode = print_mode;
    config_data.division_mode = division_mode;

    return config_data;
}

void clear_file(int core_count) {
    char filename[64];
    FILE *fptr;

    for (int id = 0; id < core_count; id++) { 
        snprintf(filename, sizeof(filename), "thread_outputs/Thread_%d.txt", id);
        fptr = fopen(filename, "w");  
        if (fptr) fclose(fptr);
    }
}

/*
    Mode: 
        0 = initial data; thread_id, minimum and maximum
        1 = write checked number
*/
void write_to_file(int mode, uint64_t lower_bound, uint64_t upper_bound,
                   int id, uint64_t prime_no, const char* time_string) {
    char filename[64];  
    snprintf(filename, sizeof(filename), "thread_outputs/Thread_%d.txt", id);

    FILE *fptr = fopen(filename, "a");
    if (!fptr) {
        perror("Error opening file");
        return;
    }

    switch (mode) {
        case 0:
            fprintf(fptr, "Thread %d\n", id);
            fprintf(fptr, "Lower Bound: %" PRIu64 "\n", lower_bound);
            fprintf(fptr, "Upper Bound: %" PRIu64 "\n\n", upper_bound);
            break;
        case 1:
            fprintf(fptr, "%s Checked: %" PRIu64 "\n", time_string, prime_no);
            break;
    }

    fclose(fptr);
}

void *prime_thread(void *arg) {
    PRIME_THREAD *pt = (PRIME_THREAD *)arg;
    int id = pt->id;
    uint64_t lower_bound = pt->lower_bound, upper_bound = pt->upper_bound;
    time_t current_time;
    char* time_string;

    write_to_file(0, lower_bound, upper_bound, id, 0, NULL);

    for (uint64_t num = lower_bound; num <= upper_bound; num++) {
        if (num < 2) continue; 

        int is_prime = 1;
        for (uint64_t check = 2; check <= (uint64_t)sqrt((long double)num); check++) {
            if (num % check == 0) {
                is_prime = 0;
                break;
            }
        }

        if (is_prime) {
            current_time = time(NULL);
            time_string = ctime(&current_time);
            time_string[strcspn(time_string, "\n")] = '\0';

            if (config.print_mode == 0) {
                printf("%s Thread %d: %" PRIu64 " is prime.\n", time_string, id, num);
                write_to_file(1, lower_bound, upper_bound, id, num, time_string);
            } else {
                pthread_mutex_lock(&result_lock);
                results[result_count].thread_id = id;
                results[result_count].prime = num;
                strncpy(results[result_count].timestamp, time_string, sizeof(results[result_count].timestamp) - 1);
                results[result_count].timestamp[sizeof(results[result_count].timestamp) - 1] = '\0';
                result_count++;
                pthread_mutex_unlock(&result_lock);
            }
        }
    }

    return NULL;
}
