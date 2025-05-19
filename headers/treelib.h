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
int is_empty_node(const tree *node);
tree *create_node_tree(list *first, list *last);
void initialise_root(tree **root, char **gen, int N, int M);
void print_tree_preorder(tree *root, FILE *fout);
char **reconstruct_generation(char **gen, int N, int M, tree *node);
void print_generation_tree_preorder(char **gen, int N, int M, int K, tree *node, FILE *fout);
void fill_tree(char **gen, int N, int M, int K, tree *root);
void free_memory_tree(tree *root);
void longest_hamiltonian_path(char **gen, int **vis, int N, int M, list **first, list **last, int *length, list **max_first, list **max_last, int *max_length);
void search_matrix_for_path(char **gen, int N, int M, FILE *fout);
void t4(char **gen, int N, int M, int K, tree *node, FILE *fout);