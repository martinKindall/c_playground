#include <stdio.h>

int main() {
    char arr[] = {'A', 'B', 'C'};
    unsigned int arr2[] = {1, 2, 3};

    char* p = arr;
    unsigned int* p2 = arr2;

    printf("char arr content: %s\n", arr);
    printf("address char arr 0: %p\n", arr);
    printf("address char arr 1: %p\n", &arr[1]);
    
    printf("\n");

    printf("address int arr 0: %p\n", arr2);
    printf("address int arr 1: %p\n", &arr2[1]);

    return 0;
}