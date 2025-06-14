#include "../headers/stacklib.h"
int is_empty_stack(const stack *top)
{
    return top == NULL;
}
void print_stack(stack *top, FILE *fout)
{
    if (is_empty_stack(top))
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
    stack *p = create_node_stack(K, first);
    if (!is_empty_stack(*top))
        p->next = (*top);
    (*top) = p;
}
void free_memory_stack(stack *top)
{
    if (is_empty_stack(top))
        return;
    free_memory_stack(top->next);
    free_memory_list(top->first);
    free(top);
}
void bonus_task2(char **gen, int N, int M, int K, stack *top, FILE *fout)
{
    while (top)
    {
        list *aux = top->first;
        while (aux)
        {
            if (gen[aux->l][aux->c] == alive)
                gen[aux->l][aux->c] = dead;
            else
                gen[aux->l][aux->c] = alive;
            aux = aux->next;
        }
        top = top->next;
    }
    free_memory_stack(top);
    print_generation(gen, N, M, 0, fout);
}