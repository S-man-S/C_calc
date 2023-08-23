#ifndef DRAW
#define DRAW

#define Y 25
#define X 80

int** createfield(int y, int x);
void memoryfree(int** field, int y);
void arrangementvalues(int** field, const int* data, int x);
void output(int** field, int* data, int y, int x);

#endif
