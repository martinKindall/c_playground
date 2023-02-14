#include <stdio.h>

void somefunction(void* something);

int main() {
    char arr[] = {'A', 'B', 'C'};
    char* p = arr;
    char achar = 'A';
    int num = 2;
    long int num2 = 2;
    unsigned short ashort = 3;

    printf("Content char array: %s\n", arr);
    printf("Size of arr: %ld\n", sizeof(arr));
    printf("Size of p: %ld\n", sizeof(p));
    printf("Size of achar: %ld\n", sizeof(achar));
    printf("Size of num: %ld\n", sizeof(num));
    printf("Size of num2: %ld\n", sizeof(num2));
    printf("Size of ashort: %ld\n", sizeof(ashort));

    somefunction(arr);

    return 0;
}

void somefunction(void* something) {
    printf("Size of something: %ld\n", sizeof(something));
    printf("Size of something 2: %ld\n", sizeof((char*)something));
    printf("Size of something 3: %ld\n", sizeof(*(char*)something));
    printf("Content char pointer: %c\n", *(char*)something);
    printf("Content char pointer 2: %c\n", *((char*)something + 1));
}
