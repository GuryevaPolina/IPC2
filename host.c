//
//  main.c
//  lab2
//
//  Created by Polina Guryeva on 01/12/2018.
//  Copyright © 2018 Polina Guryeva. All rights reserved.
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

#define N 1

sem_t* sem_host;

void clean() {
    sem_close(sem_host);
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

void calculate(int delta, int* death_in_row, int* goat_is_alive)
{
    if (*goat_is_alive && (delta > 70 / N))
    {
        *goat_is_alive = FALSE;
        printf("goat was died\n");
    }
    if (!(*goat_is_alive))
    {
        if (delta <= ceil(20 / N))
        {
            *goat_is_alive = TRUE;
            *death_in_row = -1;
            printf("goat was recover\n");
        } else {
            *death_in_row += 1;
        }
    }
}

void host()
{
    int i, delta;
    int goat_is_alive = TRUE, death_in_row = -1;
    int wolf_number, goat_number;

    printf("start game\n");
    for (i = 1;; i++)
    {
        printf("i = %i\n", i);
        //send alive state of goat
        write_data(&goat_is_alive, sizeof(int));
        sem_post(sem_host);
        wait_sem(sem_host);

        // wolf step
        wolf_number = 1 + rand() % 101;
        printf("wolf number is %i\n", wolf_number);
        
        // goat step
        read_data(&goat_number, sizeof(int));
        printf("goat number is %i\n", goat_number);
        
        delta = abs(goat_number - wolf_number);
        printf("delta is %i\n", delta);
        calculate(delta, &death_in_row, &goat_is_alive);
        
        if (death_in_row >= 2)
            break;
    }
    goat_is_alive = -1;
    write_data(&goat_is_alive, sizeof(int));

    sem_post(sem_host);
    printf("end game\n");
    clean();
}

void handle_signal(int signal){
    host();
}

struct sigaction sa;

int main(void)
{
    create_connection();
    
    sem_host = sem_open("/sem_h", O_CREAT, S_IRWXU, 0);
    if(sem_host == SEM_FAILED)
        printf("Something went wrong with semaphore...\n");
    
    sa.sa_handler = &handle_signal;
    sa.sa_flags = SA_RESTART;
    sigfillset(&sa.sa_mask);
    
    if(sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("Something went wrong with sigaction...\n");
    }
    
    while(1) {
        sleep(1);
    }
    
    return 0;
}

