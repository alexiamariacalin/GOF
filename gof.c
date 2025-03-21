#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
void read_data(int *T, int *N, int *M, int *K, char ***gen, FILE *fin)
{
    fscanf(fin, "%d %d %d %d", T, N, M, K);
    (*gen) = (char **)malloc(sizeof(char *) * (*N));
    if ((*gen) == NULL)
    {
        printf("ERROR: Could not allocate memory :(\n");
        exit(1);
    }
    char buf[2];
    for (int i = 0; i < *N; i++)
    {
        fgets(buf, 2, fin);
        (*gen)[i] = (char *)malloc(sizeof(char) * ((*M) + 1));
        (*gen)[i][*M] = '\0';
        fread((*gen)[i], sizeof((*gen)[0][0]), *M, fin);
    }
}
int main(int argc, const char *argv[])
{
    int T, M, N, K;
    char **gen;
    FILE *fin, *fout;

    open_files(&fin, &fout, argv);
    read_data(&T, &N, &M, &K, &gen, fin);
    
    return 0;
}