#include <stdio.h>

int main() {

    int num = 5;
    int* p = &num;
    int** t = &p;

    int* a = *t;
    *a = 15;

    printf("%i\n", num);

    return 0;
}