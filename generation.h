#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stacklib.h"
#include "listlib.h"
#include "treelib.h"
void print_generation(char **gen, int N, int M, int K, FILE *fout);
int in_matrix(int N, int M, int i, int j);
int count_live_cells(char **gen, int N, int M, int i, int j);
void copy_generation(char **gen, char **aux, int N, int M);
char **calculate_new_generation_standard(char **gen, int N, int M, list **first, list **last);
char **calculate_new_generation_B(char **gen, int N, int M, list **first, list **last);
char **allocate_memory_matrix(int N, int M);
void free_memory_matrix(char **gen, int N, int M);