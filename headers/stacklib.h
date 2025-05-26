#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "generation.h"
#include "listlib.h"
#define alive 'X'
#define dead '+'
typedef struct STACK
{
    int K;
    list *first, *last;
    struct STACK *next;
} stack;
int is_empty_stack(const stack *top);
void print_stack(stack *top, FILE *fout);
stack *create_node_stack(int K, list *first);
void push_node_stack(stack **top, int K, list *first);
void free_memory_stack(stack *top);
void bonus_task2(char **gen, int N, int M, int K, stack *top, FILE *fout);