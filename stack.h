#ifndef STACK
#define STACK

typedef struct node {
    char symbol;
    struct node *next;
} node;

node *init(char symbol);
void push(char symbol, node **root);
char pop(node **root);
void destroy(struct node *root);

typedef struct node_f {
    double data;
    struct node_f *next;
} node_f;

node_f *init_f(double data);
void push_f(double data, node_f **root);
double pop_f(node_f **root);
void destroy_f(struct node_f *root);

#endif
