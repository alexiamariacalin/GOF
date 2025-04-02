#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "generation.h"
#include "listlib.h"
typedef struct TREE
{
    list *first, *last;
    struct TREE *left, *right;
} tree;
tree *create_node_tree(list *first, list *last);
void initialise_tree(tree **root, char **gen, int N, int M);
void print_tree_preorder(tree *root, FILE *fout);
void reconstruct_generation_print_preorder(char **gen, int N, int M, int K, tree *node, FILE *fout);
void fill_tree(char **gen, int N, int M, int K, tree *root);