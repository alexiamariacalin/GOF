#include "../headers/generation.h"
void print_generation(char **gen, int N, int M, int K, FILE *fout)
{
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
        if (in_matrix(N, M, inew, jnew) && gen[inew][jnew] == alive)
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
char **calculate_new_generation(char **gen, int N, int M, list **first, list **last, const char *rule)
{
    char **aux = (char **)allocate_memory_matrix(N, M, sizeof(char));
    (*first) = (*last) = NULL;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            int cells = count_live_cells(gen, N, M, i, j);
            if (strcmp(rule, "standard") == 0)
                if (gen[i][j] == alive)
                    if (cells == 2 || cells == 3)
                        aux[i][j] = alive;
                    else
                        aux[i][j] = dead;
                else if (cells == 3)
                    aux[i][j] = alive;
                else
                    aux[i][j] = dead;
            else if (strcmp(rule, "B") == 0)
                if (cells == 2)
                    aux[i][j] = alive;
                else
                    aux[i][j] = gen[i][j];
            if (gen[i][j] != aux[i][j])
                add_node_list(first, last, i, j);
        }
        aux[i][M] = '\0';
    }
    return aux;
}
void **allocate_memory_matrix(int N, int M, size_t elemet_size)
{
    void **aux = (void **)calloc(N, sizeof(void *));
    if (aux == NULL)
    {
        perror("ERROR: Could not allocate memory for auxiliary matrix:(\n");
        exit(1);
    }
    for (int i = 0; i < N; i++)
    {
        aux[i] = (void *)calloc(M + 1, elemet_size);
        if (aux[i] == NULL)
        {
            perror("ERROR: Could not allocate memory for auxiliary matrix:(\n");
            exit(1);
        }
    }
    return aux;
}
void free_memory_matrix(void **gen, int N, int M)
{
    if (gen == NULL)
        return;
    for (int i = 0; i < N; i++)
        free(gen[i]);
    free(gen);
}
int count_unvisited_cells(char **gen, int **vis, int N, int M, int i, int j)
{
    const int dx[8] = {-1, -1, -1, 0, 1, 1, 1, 0};
    const int dy[8] = {-1, 0, 1, 1, 1, 0, -1, -1};
    int cells = 0;
    for (int k = 0; k < 8; k++)
    {
        int inew = i + dx[k];
        int jnew = j + dy[k];
        if (in_matrix(N, M, inew, jnew) && gen[inew][jnew] == alive && vis[inew][jnew] == 0)
            cells++;
    }
    return cells;
}
int count_group_cells(char **gen, int **vis, int N, int M, int i, int j)
{
    if (!(in_matrix(N, M, i, j) && gen[i][j] == alive && vis[i][j] == 0))
        return 0;

    const int dx[8] = {-1, -1, -1, 0, 1, 1, 1, 0};
    const int dy[8] = {-1, 0, 1, 1, 1, 0, -1, -1};

    int cells = 1;
    vis[i][j] = 1;
    
    for (int k = 0; k < 8; k++)
    {
        int inew = i + dx[k];
        int jnew = j + dy[k];
        cells += count_group_cells(gen, vis, N, M, inew, jnew);
    }
    return cells;
}