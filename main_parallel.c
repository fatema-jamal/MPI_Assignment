#include<stdio.h> 
#include<mpi.h>
#include <math.h>
#include<stdlib.h> 



//Function for reading user input

void getInput(int myRank, int comm_sz, double* angle, int* accuracy) {

	int dest;
	if (myRank == 0) {

		printf("Enter the angle in degrees:\n");
		fflush(stdout);
		scanf_s("%lf", angle);
		printf("Enter the desired accuracy :\n");
		fflush(stdout);
		scanf_s("%d", accuracy);
		for (dest = 1; dest < comm_sz; dest++) {
			MPI_Send(angle, 1, MPI_DOUBLE, dest, 0, MPI_COMM_WORLD);
			MPI_Send(accuracy, 1, MPI_INT, dest, 0, MPI_COMM_WORLD);
		}

	}
	else {
		MPI_Recv(angle, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
		MPI_Recv(accuracy, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);

	}
}



double factorial(int n)
{
	if (n > 1)
		return n * factorial(n - 1);
	else
		return 1;
}

double calcCos(double x, int k , int rank , int comm_size) {
	double in = (x * (3.14 / 180.0));
	double res = 0;
	for (double i = rank; i <=k; i+=comm_size) {
		res += (pow(-1.0, i) * pow(in, (2 * i))) / factorial(2 * i);
	}
	return res;
}

int main(void)
{
	double angle;
	int accuracy;
	int my_Rank;
	int comm_size;
	double local_sum;
	double result;
	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_Rank);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
	getInput(my_Rank,comm_size,&angle,&accuracy);

	
	
	t1 = MPI_Wtime();
	local_sum = calcCos(angle, accuracy, my_Rank, comm_size);

	MPI_Reduce(&local_sum, &result, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	t2 = MPI_Wtime();

	time = t2 - t1;
	if (my_Rank == 0) {
		printf("With %d accuracy \n", accuracy);
		fflush(stdout);
		printf("the result of cos(%f)=%f \n", angle, result);
		fflush(stdout);
		printf("Time of exexction in parallel code : %f", time);

	}
	MPI_Finalize();

}
