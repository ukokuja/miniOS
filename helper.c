//
// Created by lucas on 20/07/2021.
//

#include "helper.h"
#include <stdio.h>
#include <string.h>

#define NAME_MAX_LENGTH 19
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

void get_random_name (char* name) {
    int byte_count = MIN(strlen(name), NAME_MAX_LENGTH);
    FILE *fp;
    fp = fopen("/dev/urandom", "r");
    fread(&name, 1, byte_count, fp);
    fclose(fp);
}