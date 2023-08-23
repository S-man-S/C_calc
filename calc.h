#ifndef CALC
#define CALC
#include "stack.h"

#define SIN 's'
#define COS 'c'
#define TAN 't'
#define CTG 't'
#define SQRT 'q'
#define LN 'l'

double *process(char *input_str);
double calc(char *str, double x);
double arithmetic1(char oper, double x1);
double arithmetic2(char oper, double x1, double x2);
char *dij(char *input_str);
void pop_opers(char *str, node **root, char oper, int *ind, int *flag);
void push_oper(int *shift, char oper, node **root);
void add_to_str(char *str, char c, int *ind, int *flag);
void roundtoint(int *data, const double *doubledata, int x);

#endif
