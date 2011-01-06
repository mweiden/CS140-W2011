#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int main(int argc, char *argv[]) {
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    srand(rank);
    int i = rand();
    printf("I am process %d and i = %d\n", rank, i);
    if (rank == 0) {
        int max;
        /* In discussion, this program segfaulted.
         * The problem was the the root node needs to provide a value
         * to reduce as well as the rest of them. I was providing
         * NULL, which was bad. I now provide &i, so i is now
         * supplied as the value to reduce for the root node.
         */
        MPI_Reduce(&i, &max, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
        printf("Max was %d\n", max);
    } else {
        MPI_Reduce(&i, NULL, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
