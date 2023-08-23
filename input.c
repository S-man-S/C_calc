#include "input.h"

#include <stdlib.h>

char *inputstring() {
    char *str = malloc(1000 * sizeof(char));
    fgets(str, 1000, stdin);
    int i = 0, scob_check = 0;
    while (str[i] != '\n') {
        int shift = 1;
        if ((str[i] < '0' || str[i] > '9') && str[i] != '*' && str[i] != '-' && str[i] != '+' &&
            str[i] != '/' && str[i] != '(' && str[i] != ')' && str[i] != 'x' && str[i] != ' ' &&
            str[i] != '.') {
            scob_check += 1;
            shift = 0;
            if (str[i] == 's' && str[i + 1] == 'i' && str[i + 2] == 'n' && str[i + 3] == '(') shift = 4;
            if (str[i] == 's' && str[i + 1] == 'q' && str[i + 2] == 'r' && str[i + 3] == 't' &&
                str[i + 4] == '(')
                shift = 5;
            if (str[i] == 'c' &&
                ((str[i + 1] == 'o' && str[i + 2] == 's') || (str[i + 1] == 't' && str[i + 2] == 'g')) &&
                str[i + 3] == '(')
                shift = 4;
            if (str[i] == 't' && str[i + 1] == 'a' && str[i + 2] == 'n' && str[i + 3] == '(') shift = 4;
            if (str[i] == 'l' && str[i + 1] == 'n' && str[i + 2] == '(') shift = 3;
            if (shift == 0) {
                str = NULL;
                break;
            }
        }
        if (str[i] == '(') {
            scob_check += 1;
        }
        if (str[i] == ')') {
            scob_check -= 1;
        }
        i += shift;
    }
    if (scob_check != 0) str = NULL;
    return str;
}
