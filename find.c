#define _XOPEN_SOURCE 500
#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *pattern(char *arg)
{
    static char *pattern = NULL;
    if (pattern == NULL)
        pattern = arg;
    return pattern;
}

int display_info(const char *fpath, const struct stat *sb, int tflag, struct FTW *ftwbuf)
{

    if (strstr(fpath + ftwbuf->base, pattern(NULL)))
        printf("%s\n", fpath);
    return 0;
}

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        printf("wrong arg number. expected a string pattern to match against files and dirs. \n");
        return EXIT_FAILURE;
    }

    pattern(argv[1]);

    if (nftw(".", display_info, 100, 0) == -1)
    {
        perror("nftw");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}