#include "stacklib.h"
void print_stack(stack *top, FILE *fout)
{
    if (top == NULL)
        return;
    print_stack(top->next, fout);
    fprintf(fout, "%d ", top->K);
    print_list(top->first, fout);
}
stack *create_node_stack(int K, list *first)
{
    stack *p = (stack *)malloc(sizeof(stack));
    if (p == NULL)
    {
        perror("ERROR: Could not allocate memory for stack :(\n");
        exit(1);
    }
    p->K = K;
    p->first = first;
    p->next = NULL;
    return p;
}
void push_node_stack(stack **top, int K, list *first)
{
    if (first == NULL)
        return;
    stack *p = create_node_stack(K, first);
    if ((*top) != NULL)
        p->next = (*top);
    (*top) = p;
}
void free_memory_stack(stack *top)
{
    if (top == NULL)
        return;
    free_memory_stack(top->next);
    free_memory_list(top->first);
    free(top);
}