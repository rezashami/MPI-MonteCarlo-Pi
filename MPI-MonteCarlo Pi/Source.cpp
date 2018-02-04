#include <iostream>
#include "mpi.h"
#include <random>
#include <time.h>
#include <math.h>

using namespace std;

int main(int argc, char** argv)
{
	int myid;
	int worldSize;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &worldSize);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);

	srand(time(NULL));
	srand(time(NULL) + rand());
	srand(time(NULL) + rand());
	srand(time(NULL) + rand());
	double counter = 0;
	for (int i = 0; i < 10000000; i++)
	{
		float X = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 2));
		X -= 1.00f;
		float Y = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 2));
		Y -= 1.00f;
		if (pow(X, 2) + pow(Y, 2) <= 1) counter++;
	}
	if (myid == 0)
	{
		double sumOfCounters = counter;
		for (int i = 1; i < worldSize; i++)
		{
			double temp;
			MPI_Status st;
			MPI_Recv(&temp, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, &st);
			sumOfCounters += temp;
		}
		sumOfCounters *= 4;
		double result = (double)sumOfCounters / (double)(10000000 * worldSize);
		cout << result << "\n";
	}
	else
	{
		MPI_Send(&counter, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
	}
	MPI_Finalize();
	return 0;
}
