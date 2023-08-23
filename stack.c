#include "stack.h"

#include <stdlib.h>

node *init(char symbol) {
    node *first = malloc(sizeof(node));
    first->symbol = symbol;
    first->next = NULL;
    return first;
}

void push(char symbol, node **root) {
    node *first = malloc(sizeof(node));
    first->symbol = symbol;
    first->next = *root;
    *root = first;
}

char pop(node **root) {
    node *cur = *root;
    *root = (*root)->next;
    int ret = cur->symbol;
    free(cur);
    return ret;
}

node_f *init_f(double data) {
    node_f *first = malloc(sizeof(node_f));
    first->data = data;
    first->next = NULL;
    return first;
}

void push_f(double data, node_f **root) {
    node_f *first = malloc(sizeof(node_f));
    first->data = data;
    first->next = *root;
    *root = first;
}

double pop_f(node_f **root) {
    node_f *cur = *root;
    *root = (*root)->next;
    double ret = cur->data;
    free(cur);
    return ret;
}

void destroy_f(node_f *root) {
    node_f *cur = root;
    node_f *curn = root->next;
    while (curn != NULL) {
        free(cur);
        cur = curn;
        curn = curn->next;
    }
    free(cur);
}
