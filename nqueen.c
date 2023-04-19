/*
Written by:
    Dhruv Bhagwat
    ens22dbt@cs.umu.se
    SRM Institute of Science and Technology
*/


#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int n;
int count = 0;

int can_place(int *board, int row, int col, int *cols) {
    int i, j;
    for (i = 0; i < row; i++) {
        if (board[i] == col) return 0;
        if (abs(board[i] - col) == abs(i - row)) return 0;
    }
    for (i = 0; i < row; i++) {
        if (cols[i] == col) return 0;
    }
    return 1;
}

void nqueens(int row, int *board, int *cols) {
    int i, j, k;
    if (row == n) {
        count++;
        return;
    }
    for (i = 0; i < n; i++) {
        if (can_place(board, row, i, cols)) {
            board[row] = i;
            cols[row] = i;
            nqueens(row+1, board, cols);
            cols[row] = -1; // reset the column for backtracking
        }
    }
}

int main(int argc, char **argv) {
    int i, j, rank, size, start, end, sub_count = 0;
    int *board, *cols;
    double start_time, end_time, elapsed_time;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        printf("Enter the value of n: ");
        scanf("%d", &n);
        board = (int*) malloc(n * sizeof(int));
        cols = (int*) malloc(n * sizeof(int));
    }

    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);

    start = rank * (n / size);
    end = (rank == size - 1) ? n : (rank + 1) * (n / size);

    board = (int*) malloc(n * sizeof(int));
    cols = (int*) malloc(n * sizeof(int));
    for (i = 0; i < n; i++) {
        cols[i] = -1; // initialize with -1
    }

    start_time = MPI_Wtime();

    for (i = start; i < end; i++) {
        board[0] = i;
        cols[0] = i;
        nqueens(1, board, cols);
        cols[0] = -1; // reset the column for backtracking
    }

    MPI_Reduce(&count, &sub_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    end_time = MPI_Wtime();
    elapsed_time = end_time - start_time;

    if (rank == 0) {
        printf("Number of solutions for n=%d is %d\n", n, sub_count);
        printf("Elapsed time: %f seconds\n", elapsed_time);
    }

    MPI_Finalize();
    return 0;
}
