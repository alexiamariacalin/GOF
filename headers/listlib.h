#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct LIST
{
    int l, c;
    struct LIST *next;
} list;
int is_empty_list(const list *first);
list *create_node_list(int l, int c);
void add_node_list(list **first, list **last, int l, int c);
void print_list(list *first, FILE *fout);
void free_memory_list(list *first);
void remove_node_from_end_list(list **first, list **last);
void overwrite_list(list *first, list *last, list **max_first, list **max_last);
void print_list_formatted(list *first, FILE *fout);