//
//  client.c
//  lab2
//
//  Created by Polina Guryeva on 18/01/2019.
//  Copyright © 2019 Polina Guryeva. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <syslog.h>
#include <math.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include "connector.h"
#include <pthread.h>

sem_t* sem_client;

void clean() {
    sem_close(sem_client);
    destroy_connection();
}

void clean_with_exit()
{
    clean();
    exit(1);
}

void wait_sem(sem_t* sem)
{
    struct timespec ts;
    pthread_cond_t cond;
    clock_gettime(CLOCK_REALTIME, &ts);
    ts.tv_sec += 5;
    pthread_cond_timedwait(&cond, (pthread_mutex_t*)sem, &ts);
    
}

void client()
{
    int goat_number;
    int goat_is_alive;
    
    while (1)
    {
        // get alive state of goat
        read_data(&goat_is_alive, sizeof(int));
        
        if (goat_is_alive == -1) {
            printf("goat is died\n");
            break;
        }
        if (goat_is_alive)
            goat_number = 1 + rand() % 100;
        else
            goat_number = 1 + rand() % 50;
        
        write_data(&goat_number, sizeof(int));
        sem_post(sem_client);
    }
    sem_close(sem_client);
}

int main(int argc, char* argv[]) {
    sleep(1);
    int pid = atoi(argv[0]);
    kill(pid, SIGUSR1);
    client();
}
