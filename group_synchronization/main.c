#include "instance.h"

int main() {
    int config_type = 0;

    if(config_type == 0) {
        config = set_config();
    } else {
        config = read_config();
    }

    

    /*
        thread instances run main loop
        loop searches for players
    
    */


    return 0;
}