#include "draw.h"

#include <stdio.h>
#include <stdlib.h>

int** createfield(int y, int x) {
    int** field = (int**)calloc(y, sizeof(int*));
    for (int i = 0; i < y; ++i) {
        field[i] = (int*)calloc(x, sizeof(*field[i]));
    }
    return field;
}

void memoryfree(int** field, int y) {
    for (int i = 0; i < y; ++i) {
        free(field[i]);
    }
    free(field);
}

void arrangementvalues(int** field, const int* data, int x) {
    for (int j = 0; j < x; j++) {
        if (data[j] > -1 && data[j] < 25) {
            field[data[j]][j] = 1;
        }
    }
}

void output(int** field, int* data, int y, int x) {
    arrangementvalues(field, data, x);
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            if (field[i][j]) {
                printf("*");
            } else {
                printf(".");
            }
        }
        printf("\n");
    }
}