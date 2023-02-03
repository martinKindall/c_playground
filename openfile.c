#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define SIZE 8192

int main() {
    ssize_t n;
    char buf[SIZE];

    int fd = open("somedata.txt", O_RDONLY);

    while ((n= read(fd, buf, SIZE))>0) {
        printf("Chars read: %ld \n", n);
        printf("%.*s\n", (int)n, buf);
    }

    return 0;
}
