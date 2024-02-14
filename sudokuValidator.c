/*---------------------------------------------------------------------------
Copyright (C), 2024-2025, Sara Echeverria (bl33h)
@author Sara Echeverria
FileName: sudokuokator.c
@version: I
Creation: 13/02/2024
Last modification: 14/02/2024
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
#include <sys/wait.h>
#include <sys/syscall.h>

// macros for the sudoku grid dimensions
#define threadsN 9
#define rowsN 9
#define columnsN 9

// bidimensional array to store the sudoku grid
int sudoku[rowsN][columnsN];
int ok;

// function to check if the numbers in a row are complete and unique (not duplicated)
int rowsChecker(int row) 
{
    // array to store the numbers in the row
    int numbers[10] = {0}; 

    // iterate through the row
    for (int j = 0; j < columnsN; j++) 
    {   
        // get the number in the row
        int number = sudoku[row][j]; 
        // if the number is 0, the row is not complete
        if (number == 0) 
        {
            ok = 0;
        }

        // number of times the number appears in the row incrementer
        numbers[number]++; 

        // duplicated number checker
        if (numbers[number] > 1)  
        {
            ok = 0;
        }
    }
    return ok;
}

// function to validate each column of the sudoku grid using threads
void *columnsChecker(void *params) 
{   
    // get the thread id
    int tid = *(int *)params; 
    int numbers[threadsN] = {0};

    // iterate through the column
    for (int i = 0; i < threadsN; i++) 
    {
        // get the number in the column
        int number = sudoku[i][tid]; 
        // if the number is already in the array, it is duplicated
        if (numbers[number] == 1)  
        {
            printf("!error in column %d\n", tid + 1);
            ok = 0;
        }
        numbers[number] = 1;
    }
    printf("\n - thread number %d with PID %ld", tid+1, syscall(SYS_gettid));
    pthread_exit(0);
}

int main(int argc, char *argv[]) {
    // set the number of threads
    omp_set_num_threads(1); 
    // enable nested parallelism
    omp_set_nested(true); 

    // arguments number checker
    if (argc != 2) { 
        printf("usage: ./SudokuValidator <filename>\n");
        return 1;
    }

    // open the file
    int fd = open(argv[1], O_RDONLY); 
    if (fd == -1) {
        perror("open");
        return 1;
    }

    // get the file size
    off_t fileSize = lseek(fd, 0, SEEK_END); 

    // map the file into memory
    char *addr = mmap(NULL, fileSize, PROT_READ, MAP_PRIVATE, fd, 0);
    
    // mapping success checker
    if (addr == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    int index = 0; // index to iterate through the file
    int row, col; // row and column counters

    // sudoku grid numbers from the file filler
    for (row = 0; row < rowsN; row++) {
        for (col = 0; col < columnsN; col++) {
            char c = addr[row * 9 + col];
            sudoku[row][col] = c - '0';
        }
    }

    // print the sudoku grid
    printf("--- sudoku table ---\n");
    for (int row = 0; row < rowsN; row++) {
        for (int col = 0; col < columnsN; col++) {
            printf("%d ", sudoku[row][col]);
        }
        printf("\n");
    }

    pid_t pid; // process id
    int parentPid; // parent process id
    ok = 1; 

    parentPid = getpid(); // get the parent process id
    pid = fork(); // create a child process

    // child process
    if (pid == 0) 
    {   
        // string to store the parent process id
        char pid_str[10]; 
        sprintf(pid_str, "%d", parentPid);
        execlp("ps", "ps", "-p", pid_str, "-lLf", (char *)NULL);
        exit(0);

        // parent process
    } else {
        int columnsId[threadsN];
        pthread_t columnsT[threadsN];

        // threads creation
        for (int i = 0; i < threadsN; i++) 
        {
            columnsId[i] = i;
            pthread_create(&columnsT[i], NULL, columnsChecker, &columnsId[i]);
        }
        
        // join the threads
        for (int i = 0; i < threadsN; i++) 
        {
            pthread_join(columnsT[i], NULL);
        }
        printf("\n");
        printf("\n *the thread that executes the main is: %d\n", getpid());
        printf("\n");
        wait(NULL);
        
        // rows checker
        for (int i = 0; i < rowsN; i++) 
        {
            if (!rowsChecker(i)) 
            {
                ok = 0;
            }
        }

        // sudoku solution validation
        if (ok)
        {
            printf("\n");
            printf("--- the sudoku solution is valid ---\n");
            printf("\n");
        } else 
        {   
            printf("\n");
            printf("--- !error the sudoku solution isn't valid ---\n");
            printf("\n");
        }

        pid = fork();
        
        // child process
        if (pid == 0) 
        {
            char pid_str[10];
            sprintf(pid_str, "%d", parentPid);
            execlp("ps", "ps", "-p", pid_str, "-lLf", NULL);
            exit(0);
        } else 
        {
            wait(NULL);
            munmap(addr, fileSize);
            close(fd);
            return 0;
        }
    }
}