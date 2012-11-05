#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "mpi.h"


// Silly function for printing a vector
void printVec(double* vec, int size, int my_rank) {
	int i;
	printf("\nMYRANK %d: ", my_rank);
	for (i = 0; i < size; i ++) {
		printf("%lf ", vec[i]);
	}
	printf("\n");
}

/* Normalize vector
TESTED*/
double norm(double* unNorm, int dim) {
	int i;
	double eucDist = 0;
	
	// Sum elements
	for (i = 0; i < dim; i++)
		eucDist += unNorm[i]*unNorm[i];
		
	eucDist = sqrt(eucDist);
			
	return eucDist;
}

double min(double d1, double d2) {
	if (d1<=d2)
		return d1;
	else
		return d2;
}

int main(int argc, char** argv) {
	/* Declarations for calculations */
	// Dynamically generated vectors
	int p;
	int my_rank;	
	int i,j;
	//int n = atoi(argv[1]);
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	MPI_Status status1, status2;

	int neighbors[] = {(my_rank+(p-1))%p, (my_rank+1)%p};

	srand(time(NULL) - my_rank);

	double delta[2];
	double d=1e10;
	double dTemp;
	
	double coords[2];
	double sendVec[2];
	double loadVec[2];
	
	for (i = 0; i < 2; i++) {
		coords[i] = rand() % 20 - 10;
		sendVec[i] = coords[i];
	}
	printVec(coords,2,my_rank);
	
	for (i = 1; i < p; i++) {
		if (my_rank % 2 == 0) {
			MPI_Send(sendVec,2,MPI_DOUBLE,neighbors[1],50,MPI_COMM_WORLD);
			MPI_Recv(loadVec,2,MPI_DOUBLE,neighbors[0],50,MPI_COMM_WORLD,&status1);
		} else {
			MPI_Recv(loadVec,2,MPI_DOUBLE,neighbors[0],50,MPI_COMM_WORLD,&status2);
			MPI_Send(sendVec,2,MPI_DOUBLE,neighbors[1],50,MPI_COMM_WORLD);
		}
		for (j = 0; j < 2; j++) {
			delta[j] = coords[j] - loadVec[j];
			sendVec[j] = loadVec[j];
		}
		dTemp = norm(delta,2);
		d = min(dTemp,d);
	}

	printf("MY_RANK %d: d = %lf\n",my_rank, d);
	
	
	MPI_Finalize();
	return 0;
}
