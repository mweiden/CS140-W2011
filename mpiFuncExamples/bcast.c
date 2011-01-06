#include <stdio.h>
#include "mpi.h"

int main(int argc, char *argv[]) {
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int i = 0;
    if (rank == 0) {
        i = 42;
    }

    printf("before: %d and i = %d\n", rank, i);

    MPI_Bcast(&i, 1, MPI_INT, 0, MPI_COMM_WORLD);

    printf("after: %d and i = %d\n", rank, i);

    MPI_Finalize();
    return 0;
}
