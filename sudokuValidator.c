/*---------------------------------------------------------------------------
Copyright (C), 2024-2025, Sara Echeverria (bl33h)
@author Sara Echeverria
FileName: sudokuValidator.c
@version: I
Creation: 13/02/2024
Last modification: 13/02/2024
------------------------------------------------------------------------------*/
#include <omp.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>
#include <sys/mman.h>
#include <sys/syscall.h>

// macros for the sudoku grid dimensions
#define threadsN 9
#define rowsN 9
#define columnsN 9

// bidimensional array to store the sudoku grid
int sudoku[rowsN][columnsN];
int ok;

// function to check if the numbers in a row are complete and unique (not duplicated)
int rowsChecker() {
}

// function to validate each column of the sudoku grid using threads
int columnsChecker() {
}

int main() {}