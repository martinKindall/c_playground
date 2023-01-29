#include <stdio.h>

#define MAX_LINE 80

int main() {

    char input[MAX_LINE];
    fgets(input, MAX_LINE, stdin); 

    printf(input, "%s");

    return 0;
}