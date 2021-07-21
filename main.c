#include <stdlib.h>
#include "OS.h"
#define MAX_THREADS 10
#define MIN_THREADS 10
OS os;
char _validate_args(int argc, char **argv);

int _get_threads(char *const *argv);

int _get_clock_interval(int argc, char *const *argv);

int _get_cores(int argc, char *const *argv);

int main(int argc, char *argv[]) {
    if (!_validate_args(argc, argv))
        exit(1);
    int threads = _get_threads(argv);
    int cores = _get_cores(argc, argv);
    int clock_interval = _get_clock_interval(argc, argv);
    init_os(&os, threads, cores, clock_interval);
    run_scheduler(&os);
}


int _get_clock_interval(int argc, char *const *argv) {
    return argc > 3 ? atoi(argv[3]) : 1;
}

int _get_cores(int argc, char *const *argv) {
    return argc > 2 ? atoi(argv[2]) : 1;
}

int _get_threads(char *const *argv) {
    return atoi(argv[1]);
}

char _validate_args(int argc, char **argv) {
    return argc < 1 || atoi(argv[1]) > MAX_THREADS || atoi(argv[1]) < MIN_THREADS;
}