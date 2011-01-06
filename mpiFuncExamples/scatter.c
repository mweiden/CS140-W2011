#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int main(int argc, char *argv[]) {
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        int *i = malloc(size * sizeof(int));
        int j, k;
        for (j = 0; j < size; j++) {
            i[j] = j + 10;
        }
        MPI_Scatter(i, 1, MPI_INT, &k, 1, MPI_INT, 0, MPI_COMM_WORLD);
        printf("Got data %d on root\n", k);
    } else {
        int l;
        MPI_Scatter(NULL, 0, 0, &l, 1, MPI_INT, 0, MPI_COMM_WORLD);
        printf("Got data %d on node %d\n", l, rank);
    }

    MPI_Finalize();
    return 0;
}
