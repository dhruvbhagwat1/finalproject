/*
Written by:
    Dhruv Bhagwat
    ens22dbt@cs.umu.se
    SRM Institute of Science and Technology
*/



#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
    int i, j, start, end;
    int *board, *cols;
    double start_time, end_time, elapsed_time;

    printf("Enter the value of n: ");
    scanf("%d", &n);
    board = (int*) malloc(n * sizeof(int));
    cols = (int*) malloc(n * sizeof(int));

    for (i = 0; i < n; i++) {
        cols[i] = -1; // initialize with -1
    }

    start_time = clock();

    for (i = 0; i < n; i++) {
        board[0] = i;
        cols[0] = i;
        nqueens(1, board, cols);
        cols[0] = -1; // reset the column for backtracking
    }

    end_time = clock();
    elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("Number of solutions for n=%d is %d\n", n, count);
    printf("Elapsed time: %f seconds\n", elapsed_time);

    return 0;
}
