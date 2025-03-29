#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct LIST
{
    int l, c;
    struct LIST *next;
} list;
list *create_node_list(int l, int c);
void add_node_list(list **first, list **last, int l, int c);
void print_list(list *first, FILE *fout);