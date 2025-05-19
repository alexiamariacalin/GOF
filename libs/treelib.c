#include "../headers/treelib.h"
int is_empty_node(const tree *node)
{
    return node == NULL;
}
tree *create_node_tree(list *first, list *last)
{
    tree *p = (tree *)malloc(sizeof(tree));
    if (p == NULL)
    {
        perror("ERROR: Could not allocate memory for binary tree :(\n");
        exit(1);
    }
    p->first = first;
    p->last = last;
    p->left = NULL;
    p->right = NULL;
    return p;
}
void initialise_root(tree **root, char **gen, int N, int M)
{
    list *first = NULL;
    list *last = NULL;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            if (gen[i][j] == alive)
                add_node_list(&first, &last, i, j);
    (*root) = create_node_tree(first, last);
}
void print_tree_preorder(tree *root, FILE *fout)
{
    if (is_empty_node(root))
        return;
    print_list(root->first, fout);
    print_tree_preorder(root->left, fout);
    print_tree_preorder(root->right, fout);
}
char **reconstruct_generation(char **gen, int N, int M, tree *node)
{
    char **aux = (char **)allocate_memory_matrix(N, M, sizeof(char));
    list *aux_node = node->first;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
            if (aux_node != NULL && aux_node->l == i && aux_node->c == j)
            {
                if (gen[i][j] == alive)
                    aux[i][j] = dead;
                else
                    aux[i][j] = alive;
                aux_node = aux_node->next;
            }
            else
                aux[i][j] = gen[i][j];
        aux[i][M] = '\0';
    }
    return aux;
}
void print_generation_tree_preorder(char **gen, int N, int M, int K, tree *node, FILE *fout)
{
    if (K == 0)
        return;
    char **aux = reconstruct_generation(gen, N, M, node);
    print_generation(aux, N, M, 0, fout);
    print_generation_tree_preorder(aux, N, M, K - 1, node->left, fout);
    print_generation_tree_preorder(aux, N, M, K - 1, node->right, fout);
    free_memory_matrix((void **)aux, N, M);
}
void fill_tree(char **gen, int N, int M, int K, tree *root)
{
    if (K == 0)
        return;
    char **aux;
    list *first, *last;

    aux = calculate_new_generation(gen, N, M, &first, &last, "B");
    root->left = create_node_tree(first, last);
    fill_tree(aux, N, M, K - 1, root->left);
    free_memory_matrix((void **)aux, N, M);

    aux = calculate_new_generation(gen, N, M, &first, &last, "standard");
    root->right = create_node_tree(first, last);
    fill_tree(aux, N, M, K - 1, root->right);
    free_memory_matrix((void **)aux, N, M);
}
void free_memory_tree(tree *root)
{
    if (is_empty_node(root))
        return;
    free_memory_tree(root->left);
    free_memory_tree(root->right);
    free_memory_list(root->first);
    free(root);
}
void longest_hamiltonian_path(char **gen, int **vis, int N, int M, list **first, list **last, int *length, list **max_first, list **max_last, int *max_length)
{
    const int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    const int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

    int cells = count_unvisited_cells(gen, vis, N, M, (*last)->l, (*last)->c);
    if (cells == 0)
    {
        if ((*length) > (*max_length))
        {
            //print_list(*max_first,stdout);
            (*max_length) = (*length);
            overwrite_list(*first, *last, max_first, max_last);
        }
        return;
    }
    for (int k = 0; k < 8; k++)
    {
        int inew = (*last)->l + dx[k];
        int jnew = (*last)->c + dy[k];
        if (in_matrix(N, M, inew, jnew) && vis[inew][jnew] == 0 && gen[inew][jnew] == alive)
        {
            vis[inew][jnew] = 1;
            (*length)++;
            add_node_list(first, last, inew, jnew);

            longest_hamiltonian_path(gen, vis, N, M, first, last, length, max_first, max_last, max_length);

            vis[inew][jnew] = 0;
            (*length)--;
            remove_node_from_end_list(first, last);
        }
    }
}
void search_matrix_for_path(char **gen, int N, int M, FILE *fout)
{
    int **vis = (int **)allocate_memory_matrix(N, M, sizeof(int));
    int **big_vis = (int **)allocate_memory_matrix(N, M, sizeof(int));
    int length = 0, max_length = 0;
    list *max_first = NULL, *max_last = NULL;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            if (gen[i][j] == alive && big_vis[i][j] == 0)
            {
                int group_cells = count_group_cells(gen, big_vis, N, M, i, j);
                list *first = NULL, *last = NULL;
                vis[i][j] = 1;
                add_node_list(&first, &last, i, j);
                longest_hamiltonian_path(gen, vis, N, M, &first, &last, &length, &max_first, &max_last, &max_length);
                vis[i][j] = 0;
                free_memory_list(first);
            }
    fprintf(fout, "%d\n", max_length);
    print_list_formatted(max_first, fout);
    free_memory_list(max_first);
    free_memory_matrix((void **)vis, N, M);
    free_memory_matrix((void **)big_vis, N, M);
}
void t4(char **gen, int N, int M, int K, tree *node, FILE *fout)
{
    if (K == 0)
        return;

    char **aux = reconstruct_generation(gen, N, M, node);
    //printf("%d\n",K);
    //print_generation(aux,N,M,0,fout);
    search_matrix_for_path(aux, N, M, fout);
    t4(aux, N, M, K - 1, node->left, fout);
    t4(aux, N, M, K - 1, node->right, fout);
    free_memory_matrix((void **)aux, N, M);
}