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

// variables for the sudoku grid
#define threadsN 9
#define rowsN 9
#define colsN 9
