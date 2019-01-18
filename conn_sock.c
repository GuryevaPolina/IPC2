//
//  conn_sock.c
//  lab2
//
//  Created by Polina Guryeva on 18/01/2019.
//  Copyright © 2019 Polina Guryeva. All rights reserved.
//

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

int sockets[2];

void create_connection()
{
    if( socketpair(AF_UNIX, SOCK_STREAM, 0, sockets) == -1) {
        printf("Something went wrong with sockets...");
    }
}

void read_data(void* data, size_t size)
{
    read(sockets[0], data, size);
}

void write_data(void* data, size_t size)
{
    write(sockets[1], data, size);
}

void destroy_connection()
{
    close(sockets[0]);
    close(sockets[1]);
}
