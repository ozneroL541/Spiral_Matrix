#include <stdlib.h>
#include <math.h>
#define RIGHT 0
#define UP 1
#define LEFT 2
#define DOWN 3
#define PRINT
#undef DEBUG
#undef TIME
#ifdef TIME
    #include <stdio.h>
    #include <time.h>
#endif
#ifdef DEBUG
    #ifndef PRINT
        #define PRINT
    #endif
#endif
#ifdef PRINT
    #include <stdio.h>
#endif

/**
 * Create square matrix
 * @param n number of rows of the matrix
 * @return pointer to the matrix
*/
unsigned long ** createm(const unsigned long n) {
    unsigned long** matrix;
    unsigned long i;
    matrix = (unsigned long**) malloc(n*sizeof(unsigned long *));
    for (i = 0; i < n; i++)
        matrix[i] = (unsigned long *) malloc(n*sizeof(unsigned long));
    return matrix;
}
/**
 * Delete square matrix
 * @param matrix matrix to be freed
 * @n number of rows of the matrix
*/
void deletem(unsigned long ** matrix, const unsigned long n) {
    unsigned long i;
    for (i = 0; i < n; i++)
        free(matrix[i]);
    free(matrix);
}
#ifdef PRINT
/** 
 * Print a square matrix
 * @param matrix matrix to be printed
 * @param n number of rows of the matrix
 */
void printm(unsigned long ** matrix, unsigned long n) {
    unsigned long i = 0, j = 0;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            fprintf(stdout, "%lu\t", matrix[i][j]);
        }
        fprintf(stdout,"\n");
    }
}
#endif
/**
 * Populate the matrix
 * @param matrix
 * @param n number of rows of the matrix
*/
void populate(unsigned long ** sol, const unsigned long n) {
    /** Current direction */
    unsigned char dir = RIGHT;
    unsigned long counter = 0, i = 0, j = n -1, up_bound = 0, left_bound = 0, rigth_bound = n-1, down_bound = n -2;
    /* Increase the counter until it reaches the square of the given number */
    for (counter = 1; counter <= (n*n); counter++) {
        /* Populate the current position */
        sol[j][i] = counter;
        #ifdef DEBUG
            printf("[%d][%d] = %d\t", i, j, counter);
        #endif
        /* Move the cursor */
        switch (dir) {
            case RIGHT:
                #ifdef DEBUG
                    printf("right");
                #endif
                if (i >= rigth_bound) {
                    rigth_bound--;
                    dir = UP;
                    j--;
                } else
                    i++;
                #ifdef DEBUG
                    printf("\t%d\t%d", i, dir);
                #endif
                break;
            case DOWN:
                #ifdef DEBUG
                    printf("down");
                #endif
                if (j >= down_bound) {
                    down_bound--;
                    dir = RIGHT;
                    i++;
                } else 
                    j++;
                #ifdef DEBUG
                    printf("\t%d\t%d", i, dir);
                #endif
                break;
            case LEFT:
                #ifdef DEBUG
                    printf("left");
                #endif
                if (i <= left_bound) {
                    i = left_bound;
                    left_bound++;
                    dir = DOWN;
                    j++;
                } else
                    i--;
                #ifdef DEBUG
                    printf("\t%d\t%d", i, dir);
                #endif
                break;
            case UP:
                #ifdef DEBUG
                    printf("up");
                #endif
                if (j <= up_bound) {
                    j = up_bound;
                    up_bound++;
                    dir = LEFT;
                    i--;
                } else
                    j--;
                #ifdef DEBUG
                    printf("\t%d\t%d", i, dir);
                #endif
                break;
            default:
                #ifdef PRINT
                    fprintf(stderr, "Error: %d\n", dir);
                #endif
                break;
        }  
        #ifdef DEBUG
            printf("\n");
        #endif
    }
}

/** 
 * Generate a square matrix with an increasing number to the center.
 */
void generator(const unsigned long n) {
    /** Matrix of the solution */
    unsigned long** sol;
    #ifdef TIME
        double time_taken;
        clock_t start_time, end_time;
    #endif
    /* Create matrix */
    sol = createm(n);
    /* Populate the matrix */
    #ifdef TIME
        start_time = clock();
    #endif
    populate(sol, n);
    #ifdef TIME
        end_time = clock();
        time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
        printf("populate() took %f seconds to execute\n", time_taken);
    #endif
    /* Print solution */
    #ifdef PRINT
        printm(sol, n);
    #endif
    /* Delete matrix */
    deletem(sol, n);
}

int main(int argc, char const *argv[]) {
    unsigned long input = 0;
    if (argc < 1) {
        return 1;
    }
    input = sqrt(atoi(argv[1]));
    generator(input);
    return 0;
}
