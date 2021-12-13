#include<stdio.h>
#include<mpi.h> 
#include<stdlib.h> 
#include <math.h>
#include <time.h>


double factorial(int n)
{
	if (n > 1)
		return n * factorial(n - 1);
	else
		return 1;
}

double calcCos(double x, int k) {
	double in =( x * (3.14 / 180.0));
	double res = 0;
	for (double i = 0; i <= k; i++) {
		res += (pow(-1.0, i) * pow(in, (2 * i))) / factorial(2 * i);
	}
	return res;
}



int main(void)
{
	double angle;
	int accuracy;
	double result;
	printf("Enter the angle in degrees:\n");
	fflush(stdout);
	scanf_s("%lf", &angle);
	printf("Enter the desired accuracy :\n");
	fflush(stdout);
	scanf_s("%d", &accuracy);
	clock_t begin = clock();
	result=calcCos(angle,accuracy);
	clock_t end = clock();
	double time_spent = (double)(end - begin)*1000.0 / CLOCKS_PER_SEC;
	printf(" Cos(%f) = %f \n",angle, result);
	fflush(stdout);
	printf("Time of exexction in procedural code : %.5f", time_spent);


	return 0;
}
