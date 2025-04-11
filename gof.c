#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "generation.h"
#include "stacklib.h"
#include "listlib.h"
#include "treelib.h"
void open_files(FILE **fin, FILE **fout, const char *argv[], const int argc)
{
    if (argc < 3)
    {
        perror("ERROR: File(s) do(es)n't exist :(\n");
        exit(1);
    }
    *fin = fopen(argv[1], "rt");
    *fout = fopen(argv[2], "wt");
    if ((*fin) == NULL || (*fout) == NULL)
    {
        perror("ERROR: Could not open file(s) :(\n");
        exit(1);
    }
}
void close_files(FILE *fin, FILE *fout)
{
    if (fclose(fin) != 0 || fclose(fout) != 0)
    {
        perror("ERROR: Could not close file(s) :(\n");
        exit(1);
    }
}
void read_data(int *T, int *N, int *M, int *K, char ***gen, FILE *fin)
{
    fscanf(fin, "%d %d %d %d", T, N, M, K);
    (*gen) = allocate_memory_matrix(*N, *M);
    char buf[2];
    for (int i = 0; i < *N; i++)
    {
        fgets(buf, 2, fin);
        fread((*gen)[i], sizeof((*gen)[0][0]), *M, fin);
        (*gen)[i][*M] = '\0';
    }
}
void solve_task(int T, char **gen, int N, int M, int K, stack *top, tree *root, FILE *fout)
{
    switch (T)
    {
    case 1: // task 1
    {
        print_generation(gen, N, M, 0, fout);
        for (int i = 1; i <= K; i++)
        {
            list *first, *last;
            char **aux = calculate_new_generation(gen, N, M, &first, &last,"standard");
            copy_generation(gen, aux, N, M);
            free_memory_matrix(aux, N, M);
            free_memory_list(first);
            print_generation(gen, N, M, i, fout);
        }
        break;
    }
    case 2: // task 2
    {
        for (int i = 1; i <= K; i++)
        {
            list *first, *last;
            char **aux = calculate_new_generation(gen, N, M, &first, &last,"standard");
            copy_generation(gen, aux, N, M);
            free_memory_matrix(aux, N, M);
            push_node_stack(&top, i, first);
        }
        print_stack(top, fout);
        free_memory_stack(top);
        break;
    }
    case 3: // task 3
    {
        initialise_root(&root, gen, N, M);
        fill_tree(gen, N, M, K, root);
        print_generation(gen, N, M, K, fout);
        reconstruct_generation_print_preorder(gen, N, M, K, root->left, fout);
        reconstruct_generation_print_preorder(gen, N, M, K, root->right, fout);
        free_memory_tree(root);
        break;
    }
    case 4: // task 4
    {
        break;
    }
    }
    free_memory_matrix(gen, N, M);
}
int main(int argc, const char *argv[])
{
    int T, M, N, K;
    char **gen;
    stack *top = NULL;
    tree *root = NULL;
    FILE *fin = NULL, *fout = NULL;

    open_files(&fin, &fout, argv, argc);
    read_data(&T, &N, &M, &K, &gen, fin);
    solve_task(T, gen, N, M, K, top, root, fout);
    close_files(fin, fout);

    return 0;
}