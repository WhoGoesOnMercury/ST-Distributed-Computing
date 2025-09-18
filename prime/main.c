#include "prime.h"

int main() {
    config = read_file();

    clear_file(config.thread_count);

    PRIME_THREAD *thread_data = malloc(config.thread_count * sizeof(PRIME_THREAD));
    if (!thread_data) {
        perror("malloc failed");
        return 1;
    }

    size_t results_capacity = config.MAX_INT_VAL / 2 + 1;
    results = malloc(results_capacity * sizeof(RESULT));
    if (!results) {
        perror("malloc failed");
        free(thread_data);
        return 1;
    }

    uint64_t base_int = config.MAX_INT_VAL / config.thread_count;
    uint64_t remainder = config.MAX_INT_VAL % config.thread_count;

    for (uint64_t index = 0; index < config.thread_count; index++) {
        thread_data[index].id = index;
        if (index == 0) {
            thread_data[index].lower_bound = 0;
            thread_data[index].upper_bound = base_int + remainder;
        } else {
            thread_data[index].lower_bound = (base_int * index) + remainder;
            thread_data[index].upper_bound = (base_int * (index + 1)) + remainder;
        }
    }

    for (int t = 0; t < config.thread_count; t++) {
        pthread_create(&thread_data[t].thread, NULL, prime_thread, &thread_data[t]);
    }

    for (int t = 0; t < config.thread_count; t++) {
        pthread_join(thread_data[t].thread, NULL);
    }

    if (config.print_mode == 1) {
        printf("Printing all results:\n\n");
        Sleep(1000);

        for (size_t i = 0; i < result_count; i++) {
            printf("%s Thread %d: %llu is prime.\n",
                   results[i].timestamp,
                   results[i].thread_id,
                   results[i].prime);
        }
    }

    free(results);
    free(thread_data);

    return 0;
}