#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "generation.h"
#include "stacklib.h"
#include "listlib.h"
#include "treelib.h"
void open_files(FILE **fin, FILE **fout, const char *argv[])
{
    *fin = fopen(argv[1], "rt");
    *fout = fopen(argv[2], "wt");
    if ((*fin) == NULL || (*fout) == NULL)
    {
        printf("ERROR: Could not open file(s) :(\n");
        exit(1);
    }
}
void read_data(int *T, int *N, int *M, int *K, char ***gen, FILE *fin)
{
    fscanf(fin, "%d %d %d %d", T, N, M, K);
    (*gen) = (char **)malloc(sizeof(char *) * (*N));
    if ((*gen) == NULL)
    {
        printf("ERROR: Could not allocate memory for matrix:(\n");
        exit(1);
    }
    char buf[2];
    for (int i = 0; i < *N; i++)
    {
        fgets(buf, 2, fin);
        (*gen)[i] = (char *)malloc(sizeof(char) * ((*M) + 1));
        if ((*gen)[i] == NULL)
        {
            printf("ERROR: Could not allocate memory for matrix:(\n");
            exit(1);
        }
        (*gen)[i][*M] = '\0';
        fread((*gen)[i], sizeof((*gen)[0][0]), *M, fin);
    }
}
void TASK_1(char **gen, int N, int M, int K, stack *top, FILE *fout)
{
    print_generation(gen, N, M, 0, fout);
    for (int i = 1; i <= K; i++)
    {
        calculate_new_generation(gen, N, M, i, &top);
        print_generation(gen, N, M, i, fout);
    }
}
void TASK_2(char **gen, int N, int M, int K, stack *top, FILE *fout)
{
    for (int i = 1; i <= K; i++)
        calculate_new_generation(gen, N, M, i, &top);
    print_stack(top, fout);
}
void solve_task(int T, char **gen, int N, int M, int K, stack *top, FILE *fout)
{
    if (T == 1)
        TASK_1(gen, N, M, K, top, fout);
    if (T == 2)
        TASK_2(gen, N, M, K, top, fout);
}
int main(int argc, const char *argv[])
{
    int T, M, N, K;
    char **gen;
    stack *top = NULL;
    tree *root = NULL;
    FILE *fin, *fout;

    open_files(&fin, &fout, argv);
    read_data(&T, &N, &M, &K, &gen, fin);
    solve_task(T, gen, N, M, K, top, fout);

    return 0;
}