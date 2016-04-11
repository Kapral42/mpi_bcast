/*
 * coll.h:
 *
 * Copyright (C) 2010-2012 Mikhail Kurnosov
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>
#include <assert.h>
#include "coll.h"

#ifndef NBYTE
#define NBYTE 8
#endif

// Computes the average of an array of numbers
float compute_avg(float *array, int num_elements) {
    float sum = 0.f;
    int i;
    for (i = 0; i < num_elements; i++) {
        sum += array[i];
    }
    return sum / num_elements;
}

int main(int argc, char** argv) {

    double t = 0.0;

    MPI_Init(NULL, NULL);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int nbyte = NBYTE;
    //buffer for all process
    unsigned char *buff = malloc(nbyte);

    //init buffer only on root process
    if (world_rank == 0) {
        for (int i = 0; i < nbyte; i++) {
            buff[i] = (unsigned char) i;
        }
        printf("Buffer size: %dB\n", nbyte);
    }

    t -= MPI_Wtime();
#ifdef MPI_BC
    MPI_Bcast(buff, nbyte, MPI_CHAR, 0, MPI_COMM_WORLD);
#else
    Bcast_vdg(buff, nbyte, MPI_CHAR, 0, MPI_COMM_WORLD);
#endif
    t += MPI_Wtime();
    if (world_size <= 128) {
        printf("P: %d buff:", world_rank);
        for (int i = 0; i < nbyte; i++) {
            printf(" %d", (int) buff[i]);
        }
        printf("\n");
    } else {
        printf("P: %d buff: first(%d) last(%d)\n", world_rank,
               (int) buff[0], (int) buff[nbyte - 1]);
    }
    printf("P: %d Elapsed time time: %.6lf\n", world_rank, t);

    free(buff);
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
}
