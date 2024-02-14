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
void *columnsChecker() {
}

int main(int argc, char *argv[]) {
    omp_set_num_threads(1);
    omp_set_nested(true);

    // filename was provided as an argument checker
    if (argc != 2) {
        printf("Usage: ./SudokuValidator <filename>\n");
        return 1;
    }
    
    // open the file and map it to memory
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }
    off_t length = lseek(fd, 0, SEEK_END);
    char *addr = mmap(NULL, length, PROT_READ, MAP_PRIVATE, fd, 0);
    if (addr == MAP_FAILED) {
        perror("mmap");
        return 1;
    }
    
    // fill the sudoku bidimensional array with the numbers from the file
    int index = 0;
    int row, col;
    for (row = 0; row < NUM_ROWS; row++) {
        for (col = 0; col < NUM_COLS; col++) {
            char c = addr[row * 9 + col];
            sudoku[row][col] = c - '0';
        }
    }

    // print the sudoku grid
    printf("Sudoku table:\n");
    for (int row = 0; row < NUM_ROWS; row++) {
        for (int col = 0; col < NUM_COLS; col++) {
            printf("%d ", sudoku[row][col]);
        }
        printf("\n");
    }

    // create a child process to print the process information
    pid_t pid;
    int parentPid;
    valid = 1;

    parentPid = getpid();
}