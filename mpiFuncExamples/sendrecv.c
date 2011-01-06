#include <stdio.h>
#include "mpi.h"

int main(int argc, char *argv[]) {
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int i = 42 * rank;
    if (rank != 0) {
        MPI_Send(&i, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
        printf("Node %d sent successfully\n", rank);
    } else {
        int node;
        for (node = size - 1; node > 0; node--) {
            MPI_Recv(&i, 1, MPI_INT, node, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Received value %d from node %d\n", i, node);
        }
    }

    MPI_Finalize();
    return 0;
}
