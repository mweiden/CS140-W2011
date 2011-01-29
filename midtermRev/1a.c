#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mpi.h"

void printVec(double* vec, int size, int my_rank) {
	int i;
	printf("\nMYRANK %d: ", my_rank);
	for (i = 0; i < size; i ++) {
		printf("%lf ", vec[i]);
	}
	printf("\n");
}

int main(int argc, char** argv) {
	
	int p;
	int my_rank;	
	int i,j;
	double tempD;
	int tempI;
	int n = 12;//atoi(argv[1]);
	
	double avg;
	int above = 0;
	double sum = 0;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	MPI_Status status1;
	MPI_Status status2;
	
	srand(time(NULL) - my_rank);
	
	int nDivP = n/p;
	
	double* IQvec = malloc(sizeof(double)*nDivP);
	
	for (i = 0; i < nDivP; i++) {
		IQvec[i] = rand() % 20 + 90;
		sum += IQvec[i];
	}
	
	printVec(IQvec,nDivP,my_rank);
	
	if (my_rank != 0) {
			MPI_Send(&sum,1,MPI_DOUBLE,0,50,MPI_COMM_WORLD);
			MPI_Recv(&avg,1,MPI_DOUBLE,0,50,MPI_COMM_WORLD,&status1);
	} else {				
		for (i = 1; i < p; i++) {
			MPI_Recv(&tempD,1,MPI_DOUBLE,i,50,MPI_COMM_WORLD,&status1);
			sum += tempD;
		}
		avg = sum/n;
		for (i = 1; i < p; i++)
			MPI_Send(&avg,1,MPI_DOUBLE,i,50,MPI_COMM_WORLD);
	}
	
	// Everybody
	for (j = 0; j < nDivP; j++)
		if (IQvec[j] > avg) above++;
		
	if (my_rank != 0) {
		MPI_Send(&above,1,MPI_INT,0,50,MPI_COMM_WORLD);
	} else {
		for (i = 1; i < p; i++) {
			MPI_Recv(&tempI,1,MPI_INT,i,50,MPI_COMM_WORLD,&status1);
			above += tempI;
		}
		printf("\nSum = %lf. Above = %d. Avg = %lf \n\n",sum, above, avg);
	}
	
	free(IQvec);
	
	MPI_Finalize();
	return 0;
}