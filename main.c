#include <stdlib.h>
#include "OS/OS.h"

#define RED "\x1B[31m"
#define RESET "\x1B[0m"

OS os;


char _validate_args(int threads, int cores, int interval) {
    return threads > MIN_TASKS && threads < MAX_TASKS && cores > 0 && interval > 0;
}

int main(int argc, char *argv[]) {
    int opt;
    int threads = -1;
    int cores = 1;
    int clock_interval = 1;
    while ((opt = getopt(argc, argv, "p:n:c:")) != -1) {
        switch (opt) {
            case 'n': {
                char c[10];
                strcpy(c, optarg);
                threads = atoi(c);
                break;
            }
            case 'p': {
                char c[10];
                strcpy(c, optarg);
                cores = atoi(c);
                break;
            }
            case 'c': {
                char c[10];
                strcpy(c, optarg);
                clock_interval = atoi(c);
                break;
            }

        }
    }
    if(!_validate_args(threads, cores, clock_interval)) {
        printf("Invalid arguments\n");
        exit(1);
    }
    initOs(&os, threads, cores, clock_interval);
    runScheduler(&os);
}

