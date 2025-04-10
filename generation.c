#include "generation.h"
void print_generation(char **gen, int N, int M, int K, FILE *fout)
{
    // fprintf (fout, "A %d-a generatie:\n", K);
    for (int i = 0; i < N; i++)
    {
        fputs(gen[i], fout);
        fputs("\n", fout);
    }
    fputs("\n", fout);
}
int in_matrix(int N, int M, int i, int j)
{
    if (i >= 0 && j >= 0 && i < N && j < M)
        return 1;
    return 0;
}
int count_live_cells(char **gen, int N, int M, int i, int j)
{
    int cells = 0;
    const int dx[8] = {-1, -1, -1, 0, 1, 1, 1, 0};
    const int dy[8] = {-1, 0, 1, 1, 1, 0, -1, -1};
    for (int k = 0; k < 8; k++)
    {
        int inew = i + dx[k];
        int jnew = j + dy[k];
        if (in_matrix(N, M, inew, jnew) && gen[inew][jnew] == 'X')
            cells++;
    }
    return cells;
}
void copy_generation(char **gen, char **aux, int N, int M)
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            gen[i][j] = aux[i][j];
}
char **calculate_new_generation_standard(char **gen, int N, int M, list **first, list **last)
{
    char **aux = allocate_memory_matrix(N, M);
    (*first) = (*last) = NULL;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            int cells = count_live_cells(gen, N, M, i, j);
            if (gen[i][j] == 'X')
                if (cells == 2 || cells == 3)
                    aux[i][j] = 'X';
                else
                    aux[i][j] = '+';
            else if (cells == 3)
                aux[i][j] = 'X';
            else
                aux[i][j] = '+';
            if (gen[i][j] != aux[i][j])
                add_node_list(first, last, i, j);
        }
        aux[i][M] = '\0';
    }
    return aux;
}
char **calculate_new_generation_B(char **gen, int N, int M, list **first, list **last)
{
    char **aux = allocate_memory_matrix(N, M);
    (*first) = (*last) = NULL;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            int cells = count_live_cells(gen, N, M, i, j);
            if (cells == 2)
                aux[i][j] = 'X';
            else
                aux[i][j] = gen[i][j];
            if (gen[i][j] != aux[i][j])
                add_node_list(first, last, i, j);
        }
        aux[i][M] = '\0';
    }
    return aux;
}
char **allocate_memory_matrix(int N, int M)
{
    char **aux = (char **)malloc(sizeof(char *) * N);
    if (aux == NULL)
    {
        perror("ERROR: Could not allocate memory for auxiliary matrix:(\n");
        exit(1);
    }
    for (int i = 0; i < N; i++)
    {
        aux[i] = (char *)malloc(sizeof(char) * (M + 1));
        if (aux[i] == NULL)
        {
            perror("ERROR: Could not allocate memory for auxiliary matrix:(\n");
            exit(1);
        }
    }
    return aux;
}
void free_memory_matrix(char **gen, int N, int M)
{
    for (int i = 0; i < N; i++)
        free(gen[i]);
    free(gen);
}