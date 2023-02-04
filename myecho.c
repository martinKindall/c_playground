#include <stdio.h>

int main(void) {

    char buffer[256];

    while (fgets(buffer, sizeof(buffer), stdin)) {
        printf("%s",buffer);
    }

    return 0;
}
