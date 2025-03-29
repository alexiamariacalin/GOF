#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listlib.h"
typedef struct TREE
{
    list *first, *last;
    struct TREE *left, *right;
} tree;
tree *create_node_tree(list *first, list *last);
void initialise_tree(tree **root, char **gen, int N, int M);
void print_tree_preorder(tree *root, FILE *fout);
