/*
Short Program Demonstrating Deadlock for synchronized MPI sends/recvs
*/

#include <stdio.h>
#include "mpi.h"

int main(int argc, char** argv) {

  int size, rank;
  MPI_Status status;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  int otherAddr, dst;
  char ans[30];
  int tag = 10;

  if (rank == 0) {
    otherAddr = 1;
    char msg[] = "Hi from 0.\n";
    MPI_Ssend(&msg,strlen(msg)+1,MPI_CHAR,otherAddr,tag,MPI_COMM_WORLD); // Note this is a synchronized send!
    MPI_Recv(&ans,strlen(msg)+1,MPI_CHAR,otherAddr,tag,MPI_COMM_WORLD,&status);

  } else if (rank == 1) {
    otherAddr = 0;
    char msg[] = "Hi from 1.\n";
    MPI_Ssend(&msg,strlen(msg)+1,MPI_CHAR,otherAddr,tag,MPI_COMM_WORLD); // Note this is a synchronized send!
    MPI_Recv(&ans,strlen(msg)+1,MPI_CHAR,otherAddr,tag,MPI_COMM_WORLD,&status);
  }

  printf("Process %d speaking. I received this message: %s\n",rank,ans);

  MPI_Finalize();
  return 0;
}
