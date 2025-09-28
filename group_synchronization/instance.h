#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <time.h>
#include <windows.h>
#include <string.h>
#include <inttypes.h>

typedef struct CONFIG {
    int     n_instance_count; 
    int     t_tank_count;
    int     h_healer_count;
    int     d_dps_count;
    int     time_min;
    int     time_max;
} CONFIG;

typedef struct INSTANCE {
    bool    is_active;
} INSTANCE;

typedef struct PLAYER {
    int     player_id;
    bool    is_tank;
    bool    is_healer;
    bool    is_dps;
    bool    in_party;
} PLAYER;

typedef struct PLAYER_LIST {

} PLAYER_LIST;
