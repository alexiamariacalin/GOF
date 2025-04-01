#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stacklib.h"
#include "listlib.h"
#include "treelib.h"
void print_generation(char **gen, int N, int M, int K, FILE *fout);
int in_matrix(int N, int M, int i, int j);
int count_cells(char **gen, int N, int M, int i, int j);
void copy_generation(char **gen, char **aux, int N, int M);
void calculate_new_generation(char **gen, int N, int M, int K, stack **top);