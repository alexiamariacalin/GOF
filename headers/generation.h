#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stacklib.h"
#include "listlib.h"
#include "treelib.h"
#define alive 'X'
#define dead '+'
void print_generation(char **gen, int N, int M, int K, FILE *fout);
int in_matrix(int N, int M, int i, int j);
int count_live_cells(char **gen, int N, int M, int i, int j);
void copy_generation(char **gen, char **aux, int N, int M);
char **calculate_new_generation(char **gen, int N, int M, list **first, list **last, const char *rule);
void **allocate_memory_matrix(int N, int M, size_t elemet_size);
void free_memory_matrix(void **gen, int N, int M);
int count_unvisited_cells(char**gen, int **vis, int N, int M, int i, int j);
int count_group_cells(char **gen, int **vis, int N, int M, int i, int j);