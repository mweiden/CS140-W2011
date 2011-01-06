#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int main(int argc, char *argv[]) {
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int thing = rank + 10;

    if (rank == 0) {
        int *i = malloc(size * sizeof(int));
        int j;

        printf("Sent data %d on root\n", thing);
        MPI_Gather(&thing, 1, MPI_INT, i, 1, MPI_INT, 0, MPI_COMM_WORLD);

        for (j = 0; j < size; j++) {
            printf("i[%d] = %d\n", j, i[j]);
        }
    } else {
        printf("Set data %d on node %d\n", thing, rank);
        MPI_Gather(&thing, 1, MPI_INT, 0, 0, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
