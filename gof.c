#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct LIST
{
    int l, c;
    struct LIST *next;
} list;
typedef struct STACK
{
    int K;
    list *first, *last;
    struct STACK *next;
} stack;
stack *top = NULL;
typedef struct TREE
{
    list *first, *last;
    struct TREE *left, *right;
} tree;
tree *root = NULL;
list *create_node_list(int l, int c)
{
    list *p = (list *)malloc(sizeof(list));
    if (p == NULL)
    {
        printf("ERROR: Could not allocate memory for list :(\n");
        exit(1);
    }
    p->l = l;
    p->c = c;
    p->next = NULL;
    return p;
}
void add_node_list(list **first, list **last, int l, int c)
{
    list *p = create_node_list(l, c);
    if ((*first) == NULL)
        (*first) = (*last) = p;
    else
    {
        (*last)->next = p;
        (*last) = p;
    }
}
void print_list(list *first, FILE *fout)
{
    while (first->next != NULL)
    {
        fprintf(fout, "%d %d ", first->l, first->c);
        first = first->next;
    }
    fprintf(fout, "%d %d", first->l, first->c);
    fprintf(fout, "\n");
}
tree *create_node_tree(list *first, list *last)
{
    tree *p = (tree *)malloc(sizeof(tree));
    if (p == NULL)
    {
        printf("ERROR: Could not allocate memory for binary tree :(\n");
        exit(1);
    }
    p->first = first;
    p->last = last;
    p->left = NULL;
    p->right = NULL;
    return p;
}
void initialise_tree(tree **root, char **gen, int N, int M)
{
    list *first = NULL;
    list *last = NULL;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            if (gen[i][j] == 'X')
                add_node_list(&first, &last, i, j);
    (*root) = create_node_tree(first, last);
}
void print_tree_preorder(tree *root, FILE *fout)
{
    if (root == NULL)
        return;
    print_list(root->first, fout);
    print_tree_preorder(root->left, fout);
    print_tree_preorder(root->right, fout);
}
void print_stack(stack *top, FILE *fout)
{
    if (top == NULL)
        return;
    print_stack(top->next, fout);
    fprintf(fout, "%d ", top->K);
    print_list(top->first, fout);
}
stack *create_node_stack(int K, list *first)
{
    stack *p = (stack *)malloc(sizeof(stack));
    if (p == NULL)
    {
        printf("ERROR: Could not allocate memory for stack :(\n");
        exit(1);
    }
    p->K = K;
    p->first = first;
    p->next = NULL;
    return p;
}
void push_node_stack(stack **top, int K, list *first)
{
    if (first == NULL)
        return;
    stack *p = create_node_stack(K, first);
    if ((*top) != NULL)
        p->next = (*top);
    (*top) = p;
}
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
int in_matrix(int N, int M, int i, int j)
{
    if (i >= 0 && j >= 0 && i < N && j < M)
        return 1;
    return 0;
}
int count_cells(char **gen, int N, int M, int i, int j)
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
void calculate_new_generation(char **gen, int N, int M, int K)
{
    char **aux;
    aux = (char **)malloc(sizeof(char *) * N);
    list *first = NULL;
    list *last = NULL;
    if (aux == NULL)
    {
        printf("ERROR: Could not allocate memory for auxiliary matrix:(\n");
        exit(1);
    }
    for (int i = 0; i < N; i++)
    {
        aux[i] = (char *)malloc(sizeof(char) * (M + 1));
        if (aux[i] == NULL)
        {
            printf("ERROR: Could not allocate memory for auxiliary matrix:(\n");
            exit(1);
        }
        for (int j = 0; j < M; j++)
        {
            int cells = count_cells(gen, N, M, i, j);
            // printf("%d ", cells);
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
                add_node_list(&first, &last, i, j);
        }
        aux[i][M] = '\0';
        // printf("\n");
    }
    copy_generation(gen, aux, N, M);
    push_node_stack(&top, K, first);
}
void TASK_1(char **gen, int N, int M, int K, FILE *fout)
{
    print_generation(gen, N, M, 0, fout);
    for (int i = 1; i <= K; i++)
    {
        calculate_new_generation(gen, N, M, i);
        print_generation(gen, N, M, i, fout);
    }
}
void TASK_2(char **gen, int N, int M, int K, FILE *fout)
{
    for (int i = 1; i <= K; i++)
        calculate_new_generation(gen, N, M, i);
    print_stack(top, fout);
}
void solve_task(int T, char **gen, int N, int M, int K, FILE *fout)
{
    if (T == 1)
        TASK_1(gen, N, M, K, fout);
    if (T == 2)
        TASK_2(gen, N, M, K, fout);
}
int main(int argc, const char *argv[])
{
    int T, M, N, K;
    char **gen;
    FILE *fin, *fout;

    open_files(&fin, &fout, argv);
    read_data(&T, &N, &M, &K, &gen, fin);
    solve_task(T, gen, N, M, K, fout);

    return 0;
}