//
//  conn_pipe.c
//  lab2
//
//  Created by Polina Guryeva on 01/12/2018.
//  Copyright © 2018 Polina Guryeva. All rights reserved.
//

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#include "connector.h"

int desc[2];

void create_connection()
{
    if(pipe(desc) == -1) {
        printf("Something went wrong with pipe...");
    }
}

void read_data(void* data, size_t size)
{
    read(desc[0], data, size);
}

void write_data(void* data, size_t size)
{
    write(desc[1], data, size);
}

void destroy_connection()
{
    close(desc[0]);
    close(desc[1]);
}
