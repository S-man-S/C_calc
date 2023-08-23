#include <math.h>
#include <stdlib.h>

#include "calc.h"
#include "draw.h"
#include "input.h"

int main() {
    char *str = inputstring();
    if (str) {
        double *mass = process(str);
        int **field = createfield(Y, X);
        int *test = (int *)malloc(X * sizeof(int));
        roundtoint(test, mass, X);
        output(field, test, Y, X);
        memoryfree(field, Y);
        free(test);
        free(mass);

    } else{
        printf("n/a");
	free(str);
    }

    return 0;
}
