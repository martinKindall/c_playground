#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 80

int main(void) {

    char* args[MAX_LINE/2 + 1];
    int should_run = 1;

    while (should_run) {
        printf("morsa>");
        fflush(stdout);

        char str[MAX_LINE];
        fgets(str, MAX_LINE, stdin); 

        char ** res  = NULL;
        char *  p    = strtok (str, " ");
        int n_spaces = 0, i;

        while (p) {
            res = realloc (res, sizeof (char*) * ++n_spaces);

            if (res == NULL)
                exit (-1);

            res[n_spaces-1] = p;

            p = strtok (NULL, " ");
        }

        res = realloc (res, sizeof (char*) * (n_spaces+1));
        res[n_spaces] = 0;   // end of array

        for (i = 0; i < (n_spaces+1); ++i)
            printf ("res[%d] = %s\n", i, res[i]);

        free (res);

        should_run = 0;
    }

    return 0;
}