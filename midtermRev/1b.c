#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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
	/* Declarations for calculations */
	// Dynamically generated vectors
	int p;
	int my_rank;	
	int i,j;
	double tempD;
	int tempI;
	char * pEnd;
	int n = atoi(argv[1]);
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &p);

	int nDivP = n/p;
	double avg;
	int myAbove = 0;
	int above;

	srand(my_rank);

	double sum;
	double mySum;
	
	double* IQvec = malloc(sizeof(double)*nDivP);
	
	for (i = 0; i < nDivP; i++) {
		IQvec[i] = rand() % 20 + 90;
		mySum += IQvec[i];
	}
	printVec(IQvec,nDivP,my_rank);
	
	//
	MPI_Reduce(&mySum,&sum,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
	
	MPI_Bcast(&sum,1,MPI_DOUBLE,0,MPI_COMM_WORLD);
	
	avg = sum / n;
	
	// Everybody
	for (j = 0; j < nDivP; j++)
		if (IQvec[j] > avg) myAbove++;
		
	MPI_Reduce(&myAbove,&above,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
	
	if (my_rank == 0)
		printf("\nSum = %lf. Above = %d. Avg = %lf \n\n",sum, above, avg);

	free(IQvec);
	
	
	
	
	MPI_Finalize();
	return 0;
}