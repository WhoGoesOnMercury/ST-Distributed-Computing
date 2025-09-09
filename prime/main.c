#include "prime.h"

int main() {
    CONFIG config;
    config = read_file();

    PRIME_THREAD *thread_data = malloc(config.thread_count * sizeof(PRIME_THREAD));

    int base_int = 0, remainder = 0;

    base_int = config.MAX_INT_VAL / config.thread_count;
    remainder = config.MAX_INT_VAL % config.thread_count;

    for(int index = 0; index < config.thread_count; index++) {
        thread_data[index].id = index;
        if(index == 0) {
            thread_data[index].lower_bound = 0;
            thread_data[index].upper_bound = base_int + remainder;
        } else {
            thread_data[index].lower_bound = (base_int * index) + remainder;
            thread_data[index].upper_bound = (base_int * (index + 1)) + remainder;
        }
    }

    int t_count = 0;
    for(t_count = 0; t_count < config.thread_count; t_count++) {
        pthread_create(&thread_data[t_count].thread, NULL, prime_thread, &thread_data[t_count]);
    }

    for(t_count = 0; t_count < config.thread_count; t_count++) {
        pthread_join(thread_data[t_count].thread, NULL);
    }

    free(thread_data);

    return 0;
}