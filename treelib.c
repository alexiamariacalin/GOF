#include "treelib.h"
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
void reconstruct_generation_print_preorder(char **gen, int N, int M, int K, tree *node, FILE *fout)
{
    if (K == 0)
        return;
    char **aux = (char **)malloc(sizeof(char *) * N);
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
            if (node->first != NULL && node->first->l == i && node->first->c == j)
            {
                if (gen[i][j] == 'X')
                    aux[i][j] = '+';
                else
                    aux[i][j] = 'X';
                node->first = node->first->next;
            }
            else
                aux[i][j] = gen[i][j];
        aux[i][M] = '\0';
    }
    print_generation(aux, N, M, 0, fout);
    reconstruct_generation_print_preorder(aux, N, M, K - 1, node->left, fout);
    reconstruct_generation_print_preorder(aux, N, M, K - 1, node->right, fout);
}
void fill_tree(char **gen, int N, int M, int K, tree *root)
{
    if (K == 0)
        return;
    char **auxl = (char **)malloc(sizeof(char *) * N);
    char **auxr = (char **)malloc(sizeof(char *) * N);
    for (int i = 0; i < M; i++)
    {
        auxl[i] = (char *)malloc(sizeof(char) * (M + 1));
        auxr[i] = (char *)malloc(sizeof(char) * (M + 1));
    }
    copy_generation(auxl, gen, N, M);
    copy_generation(auxr, gen, N, M);

    list *first, *last;

    auxl = calculate_new_generation_B(auxl, N, M, &first, &last);
    // printf("left: ");
    // print_list(first, stdout);
    root->left = create_node_tree(first, last);
    fill_tree(auxl, N, M, K - 1, root->left);

    auxr = calculate_new_generation_standard(auxr, N, M, &first, &last);
    // printf("right: ");
    // print_list(first, stdout);
    // printf("*\n\n");
    root->right = create_node_tree(first, last);
    fill_tree(auxr, N, M, K - 1, root->right);
}