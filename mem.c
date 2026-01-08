#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "common.h"

int main(int argc, char *argv[])
{
    int *p = malloc(sizeof(int));
    assert(p != NULL);

    printf("(%d) address pointed to by p: %p\n", getpid(), p);

    *p = 0;

    while (1) {
        Spin(1);            // spin for 1 second (burn CPU)
        *p = *p + 1;        // increment the value stored at the allocated memory
        printf("(%d) p: %d\n", getpid(), *p);
    }

    return 0;
}

