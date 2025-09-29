#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <time.h>
#include <windows.h>
#include <string.h>
#include <inttypes.h>

typedef struct CONFIG {
    int         instance_count; 
    int         tank_count;
    int         healer_count;
    int         dps_count;
    int         time_min;
    int         time_max;
    int         party_count;
} CONFIG;

typedef struct INSTANCE {
    pthread_t   thread;
    int         id;
    bool        is_party_complete;
    int         time_min;
    int         time_max;
    int         *player_ids;

} INSTANCE;

typedef struct PLAYER {
    int         player_id;
    bool        is_tank;
    bool        is_healer;
    bool        is_dps;
    bool        in_party;
} PLAYER;

typedef struct PLAYER_LIST {
    PLAYER      *players = NULL;
    int         tank_count;
    int         healer_count;
    int         dps_count;
} PLAYER_LIST;

/*
    Global variables
*/
CONFIG config;
PLAYER *players = NULL;
size_t player_count = 0;

CONFIG set_config() {
    CONFIG config_data;

    printf("Enter maximum number of concurrent instances: ");
    scanf("%d", config_data->instance_count);

    printf("Enter number of tanks in the queue: ");
    scanf("%d", config_data->tank_count);

    printf("Enter number of healers in the queue: ");
    scanf("%d", config_data->healer_count);

    printf("Enter number of DPS in the queue: ");
    scanf("%d", config_data->dps_count);

    printf("Enter minimum instance completion time: ");
    scanf("%d", config_data->time_min);

    printf("Enter maximum instance completion time: ");
    scanf("%d", config_data->time_max);

    return config_data;
}

CONFIG read_config() {
    CONFIG config_data;
    int n = 0, t = 0, d = 0, h = 0, tmin = 0, tmax = 0;

    FILE *fptr = fopen("config.txt", "r");
    if (!fptr) {
        perror("Error opening config.txt");
        exit(1);
    }

    if (fscanf(fptr, "%d", &n) != 1) {
        fprintf(stderr, "Invalid instance_count in config.txt\n");
        exit(1);
    }
    if (fscanf(fptr, "%d", &t) != 1) {
        fprintf(stderr, "Invalid tank_count in config.txt\n");
        exit(1);
    }
    if (fscanf(fptr, "%d", &h) != 1) {
        fprintf(stderr, "Invalid healer_count in config.txt\n");
        exit(1);
    }
    if (fscanf(fptr, "%d", &d) != 1) {
        fprintf(stderr, "Invalid dps_count in config.txt\n");
        exit(1);
    }
    if (fscanf(fptr, "%d", &tmin) != 1) {
        fprintf(stderr, "Invalid time_min in config.txt\n");
        exit(1);
    }
    if (fscanf(fptr, "%d", &tmax) != 1) {
        fprintf(stderr, "Invalid time_max in config.txt\n");
        exit(1);
    }

    fclose(fptr);

    config_data.instance_count = n;
    config_data.tank_count = t;
    config_data.healer_count = h;
    config_data.dps_count = d;
    config_data.time_min = tmin;
    config_data.time_max = tmax;

    return config_data;
}

void *instance_thread(void *arg) {

    if(is_party_complete == 1) {

    } else {

    }

    // Search again for players

    return NULL;
}