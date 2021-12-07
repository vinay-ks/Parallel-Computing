#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
using namespace std;

int main(int argc, char** argv) {
    // freopen("input.txt", "r", stdin);
    srand(time(0));

    int n, pid, np, elements_per_process, n_elements_recieved;
    scanf("%d", &n);


    int a[n];
       

    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &pid);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
    if (pid == 0) {
        for(int i=0;i<n;i++)
        a[i] = rand()%10;    

        // for(int i=0;i<n;i++)
        //         printf("%d ",a[i]);
        // printf("\n\n");
		int index, i;
		elements_per_process = n / np;

		if (np > 1) {
			for (i = 1; i < np - 1; i++) {
				index = i * elements_per_process;
				MPI_Send(&elements_per_process, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
				MPI_Send(&a[index], elements_per_process, MPI_INT, i, 0, MPI_COMM_WORLD);
			}

			index = i * elements_per_process;
			int elements_left = n - index;

			MPI_Send(&elements_left, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
			MPI_Send(&a[index], elements_left, MPI_INT, i, 0, MPI_COMM_WORLD);
		}

		int sum = 0;
		for (i = 0; i < elements_per_process; i++)
			sum += a[i];

		int tmp;
		for (i = 1; i < np; i++) {
			MPI_Recv(&tmp, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
			int sender = status.MPI_SOURCE;

			sum += tmp;
		}

		printf("Array Sum : %d\n", sum);
	}


	else {
        int a2[n/np];
		MPI_Recv(&n_elements_recieved, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

		MPI_Recv(&a2, n_elements_recieved, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

		int partial_sum = 0;
		for (int i = 0; i < n_elements_recieved; i++)
			partial_sum += a2[i];

		MPI_Send(&partial_sum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}

	MPI_Finalize();

	return 0;
}
