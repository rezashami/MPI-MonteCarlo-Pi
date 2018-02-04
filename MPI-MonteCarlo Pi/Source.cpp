#include <iostream>
#include "mpi.h"
#include <random>

using namespace std;

int main(int argc, char** argv)
{
	int myid;
	int worldSize;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &worldSize);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);


}