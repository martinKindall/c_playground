#include <stdio.h>

#define MAX_LINE 80

int main() {

    char myString[MAX_LINE];

    scanf("%s", myString);

    printf("bye\n");
    printf(myString, "%s");

    return 0;
}