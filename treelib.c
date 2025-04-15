#include "treelib.h"
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
            if (gen[i][j] == 'X')
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
void reconstruct_generation_print_preorder(char **gen, int N, int M, int K, tree *node, FILE *fout)
{
    if (K == 0)
        return;
    char **aux = allocate_memory_matrix(N, M);
    list *aux_node = node->first;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
            if (aux_node != NULL && aux_node->l == i && aux_node->c == j)
            {
                if (gen[i][j] == 'X')
                    aux[i][j] = '+';
                else
                    aux[i][j] = 'X';
                aux_node = aux_node->next;
            }
            else
                aux[i][j] = gen[i][j];
        aux[i][M] = '\0';
    }
    print_generation(aux, N, M, 0, fout);
    reconstruct_generation_print_preorder(aux, N, M, K - 1, node->left, fout);
    reconstruct_generation_print_preorder(aux, N, M, K - 1, node->right, fout);
    free_memory_matrix(aux, N, M);
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
    free_memory_matrix(aux, N, M);

    aux = calculate_new_generation(gen, N, M, &first, &last, "standard");
    root->right = create_node_tree(first, last);
    fill_tree(aux, N, M, K - 1, root->right);
    free_memory_matrix(aux, N, M);
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