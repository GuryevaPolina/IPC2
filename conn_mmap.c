//
//  conn_mmap.c
//  lab2
//
//  Created by Polina Guryeva on 01/12/2018.
//  Copyright © 2018 Polina Guryeva. All rights reserved.
//

#include <sys/types.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#include "connector.h"
#define SIZE 100
void *buf = NULL;


void create_connection()
{
    if((buf = mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0)) == MAP_FAILED) {
        printf("Something went wrong with mmap...\n");
        buf = NULL;
    }
}

void read_data(void* data, size_t size)
{
    memcpy(data, buf, size);
}

void write_data(void* data, size_t size)
{
    memcpy(buf, data, size);
}

void destroy_connection()
{
    munmap(buf, SIZE);
}
