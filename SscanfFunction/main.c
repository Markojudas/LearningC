#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv)
{
    char cmd[512];
    int n, d0, m0, y0, d1, m1, y1 = 0;

    if (argc != 2){
        printf("usage: %s <cmd string>\n", argv[0]);
        return 1;
    }

    n = sscanf(argv[1], "%s %d/%d/%d %d/%d/%d",
               cmd, &d0, &m0, &y0, &d1, &m1, &y1);

    if(!strcmp(cmd, "print") && n == 4){
        printf("")
    }
}
