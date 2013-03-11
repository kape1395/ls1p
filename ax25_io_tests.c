#include <stdlib.h>
#include <stdio.h>
#include "ax25_io.h"

int main(int argn, char** argv)
{
    int rc;
    int sock;

    rc = ax25_init(&sock, "1", "OH2BNS");
    fprintf(stderr, "ax25_init, rc=%d\n", rc);

    return EXIT_SUCCESS;
}
