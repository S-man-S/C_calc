#include "calc.h"

#include <math.h>
#include <stdlib.h>

double *process(char *input_str) {
    double *mass = malloc(80 * sizeof(double));
    char *str = dij(input_str);
    double step = 4 * M_PI / 79;
    for (int i = 0; i < 80; i++) mass[i] = calc(str, step * i);
    free(str);
    return mass;
}

double calc(char *str, double x) {
    node_f *numbers = init_f(666);
    while (str[0] != '\n' && str[0] != '\0') {
        if (str[0] == ' ')
            str = str + 1;
        else {
            if (str[0] == 'x' || (str[0] == '-' && str[1] == 'x')) {
                if (str[0] == 'x')
                    push_f(x, &numbers);
                else {
                    push_f(-1 * x, &numbers);
                    str = str + 1;
                }
                str = str + 1;
            } else {
                if ((str[0] >= '0' && str[0] <= '9') || (str[0] == '-' && (str[1] >= '0' && str[1] <= '9'))) {
                    if (str[0] == '-') {
                        str = str + 1;
                        push_f(-1 * strtod(str, &str), &numbers);
                    } else
                        push_f(strtod(str, &str), &numbers);
                } else {
                    if (str[0] == '+' || str[0] == '*' || str[0] == '-' || str[0] == '/') {
                        double res = arithmetic2(str[0], pop_f(&numbers), pop_f(&numbers));
                        if (!numbers) numbers = init_f(666);
                        push_f(res, &numbers);
                    } else {
                        double res = arithmetic1(str[0], pop_f(&numbers));
                        if (!numbers) numbers = init_f(666);
                        push_f(res, &numbers);
                    }
                    str = str + 1;
                }
            }
        }
    }
    double res = pop_f(&numbers);
    destroy_f(numbers);
    return res;
}

double arithmetic1(char oper, double x1) {
    double res;
    if (oper == SIN) res = sin(x1);
    if (oper == COS) res = cos(x1);
    if (oper == TAN) res = tan(x1);
    if (oper == CTG) res = 1.0 / tan(x1);
    if (oper == SQRT) res = sqrt(x1);
    if (oper == LN) res = log(x1);
    return res;
}

double arithmetic2(char oper, double x1, double x2) {
    double res;
    if (oper == '+') res = x1 + x2;
    if (oper == '-') res = x1 - x2;
    if (oper == '*') res = x1 * x2;
    if (oper == '/') res = x1 / x2;
    return res;
}

char *dij(char *str) {
    char *output_str = malloc(1000 * sizeof(char));
    int i = 0, j = 0, flag = 0, flag_minus = 1, shift;
    node *root = init('.');
    while (str[i] != '\n') {
        shift = 1;
        if (str[i] == ' ') flag = 1;
        if ((str[i] >= '0' && str[i] <= '9') || str[i] == 'x' || str[i] == '.' ||
            (flag_minus == 1 && str[i] == '-')) {
            add_to_str(output_str, str[i], &j, &flag);
            flag_minus = 0;
        } else {
            if (str[i] == '+') {
                pop_opers(output_str, &root, '+', &j, &flag);
                push_oper(&shift, '+', &root);
                flag_minus = 1;
            }
            if (str[i] == '-' && flag_minus == 0) {
                pop_opers(output_str, &root, '-', &j, &flag);
                push_oper(&shift, '-', &root);
                flag_minus = 1;
            }
            if (str[i] == '*') {
                pop_opers(output_str, &root, '*', &j, &flag);
                push_oper(&shift, '*', &root);
                flag_minus = 1;
            }
            if (str[i] == '/') {
                pop_opers(output_str, &root, '/', &j, &flag);
                push_oper(&shift, '/', &root);
                flag_minus = 1;
            }
            if (str[i] == '(') {
                pop_opers(output_str, &root, '(', &j, &flag);
                push_oper(&shift, '(', &root);
                flag_minus = 1;
            }
            if (str[i] == ')') {
                pop_opers(output_str, &root, ')', &j, &flag);
            }
            if (str[i] == 's' && str[i + 1] == 'i' && str[i + 2] == 'n' && str[i + 3] == '(') {
                pop_opers(output_str, &root, SIN, &j, &flag);
                push_oper(&shift, SIN, &root);
                flag_minus = 1;
            }
            if (str[i] == 's' && str[i + 1] == 'q' && str[i + 2] == 'r' && str[i + 3] == 't' &&
                str[i + 4] == '(') {
                pop_opers(output_str, &root, SQRT, &j, &flag);
                push_oper(&shift, SQRT, &root);
                flag_minus = 1;
            }
            if (str[i] == 'c' && str[i + 1] == 'o' && str[i + 2] == 's' && str[i + 3] == '(') {
                pop_opers(output_str, &root, COS, &j, &flag);
                push_oper(&shift, COS, &root);
                flag_minus = 1;
            }
            if (str[i] == 'c' && str[i + 1] == 't' && str[i + 2] == 'g' && str[i + 3] == '(') {
                pop_opers(output_str, &root, CTG, &j, &flag);
                push_oper(&shift, CTG, &root);
                flag_minus = 1;
            }
            if (str[i] == 't' && str[i + 1] == 'a' && str[i + 2] == 'n' && str[i + 3] == '(') {
                pop_opers(output_str, &root, TAN, &j, &flag);
                push_oper(&shift, TAN, &root);
                flag_minus = 1;
            }
            if (str[i] == 'l' && str[i + 1] == 'n' && str[i + 2] == '(') {
                pop_opers(output_str, &root, LN, &j, &flag);
                push_oper(&shift, LN, &root);
                flag_minus = 1;
            }
        }
        i += shift;
    }
    pop_opers(output_str, &root, '.', &j, &flag);
    free(str);
    output_str[j] = '\n';
    return output_str;
}

void pop_opers(char *str, node **root, char oper, int *ind, int *flag) {
    if (oper == '.') {
        while (1) {
            *flag = 1;
            char c = pop(root);
            if (c == '.') {
                break;
            } else {
                if (c == '(' || c == SIN || c == COS || c == TAN || c == SQRT || c == LN || c == CTG) {
                    break;
                } else {
                    add_to_str(str, c, ind, flag);
                }
            }
        }
    }
    if (oper == ')') {
        while (1) {
            *flag = 1;
            char c = pop(root);
            if (c == '(') {
                break;
            } else {
                if (c == SIN || c == COS || c == TAN || c == SQRT || c == LN || c == CTG) {
                    add_to_str(str, c, ind, flag);
                    break;
                } else {
                    add_to_str(str, c, ind, flag);
                }
            }
        }
    }
    if (oper == '+' || oper == '-') {
        while (1) {
            *flag = 1;
            char c = pop(root);
            if (c == '+' || c == '-' || c == '*' || c == '/') {
                add_to_str(str, c, ind, flag);
            } else {
                if (c == '.') {
                    *root = init(c);
                } else {
                    push(c, root);
                }
                break;
            }
        }
    }
    if (oper == '*' || oper == '/') {
        while (1) {
            *flag = 1;
            char c = pop(root);
            if (c == '*' || c == '/') {
                add_to_str(str, c, ind, flag);
            } else {
                if (c == '.') {
                    *root = init(c);
                } else {
                    push(c, root);
                }
                break;
            }
        }
    }
}

void push_oper(int *shift, char oper, node **root) {
    push(oper, root);
    if (oper == '+' || oper == '-' || oper == '*' || oper == '/' || oper == '(') *shift = 1;
    if (oper == LN) *shift = 3;
    if (oper == SIN || oper == COS || oper == CTG || oper == TAN) *shift = 4;
    if (oper == SQRT) *shift = 5;
}

void add_to_str(char *str, char c, int *ind, int *flag) {
    if (*flag) {
        str[(*ind)++] = ' ';
        *flag = 0;
    }
    str[(*ind)++] = c;
}

void roundtoint(int *data, const double *doubledata, int x) {
    for (int j = 0; j < x; j++) {
        data[j] = (int)round((doubledata[j] + 1) / 0.083333);
    }
}
