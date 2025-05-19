#include "../headers/listlib.h"
int is_empty_list(const list *first)
{
    return first == NULL;
}
list *create_node_list(int l, int c)
{
    list *p = (list *)malloc(sizeof(list));
    if (p == NULL)
    {
        perror("ERROR: Could not allocate memory for list :(\n");
        exit(1);
    }
    p->l = l;
    p->c = c;
    p->next = NULL;
    return p;
}
void add_node_list(list **first, list **last, int l, int c)
{
    list *p = create_node_list(l, c);
    if ((*first) == NULL)
        (*first) = (*last) = p;
    else
    {
        (*last)->next = p;
        (*last) = p;
    }
}
void print_list(list *first, FILE *fout)
{
    if (is_empty_list(first))
        return;
    while (first->next != NULL)
    {
        fprintf(fout, "%d %d ", first->l, first->c);
        first = first->next;
    }
    fprintf(fout, "%d %d", first->l, first->c);
    fprintf(fout, "\n");
}
void free_memory_list(list *first)
{
    if (is_empty_list(first))
        return;
    free_memory_list(first->next);
    free(first);
}
void remove_node_from_end_list(list **first, list **last)
{
    if (is_empty_list(*first))
        return;
    if ((*first) == (*last))
    {
        free(*first);
        (*first) = (*last) = NULL;
        return;
    }
    list *aux = (*first);
    while (aux->next != (*last))
        aux = aux->next;
    aux->next = NULL;
    free(*last);
    (*last) = aux;
}
void overwrite_list(list *first, list *last, list **max_first, list **max_last)
{
    list *aux = (*max_first);
    while (aux != NULL)
    {
        aux->l = first->l;
        aux->c = first->c;
        aux = aux->next;
        first = first->next;
    }
    while (first != NULL)
    {
        add_node_list(max_first, max_last, first->l, first->c);
        first = first->next;
    }
}
void print_list_formatted(list *first, FILE *fout)
{
    if (is_empty_list(first))
        return;
    while (first->next != NULL)
    {
        fprintf(fout, "(%d,%d) ", first->l, first->c);
        first = first->next;
    }
    fprintf(fout, "(%d,%d)", first->l, first->c);
    fprintf(fout, "\n");
}