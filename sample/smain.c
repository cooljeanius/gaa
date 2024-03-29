/* main file corresponding to sample.gaa */
#include <stdio.h>
#ifdef GAA_WORKS
# include "sample_gaa.h"
#else
struct gaainfo
{
    int n;
    const char *file;
    int verbose;
    int size;
    const char **input;
};
typedef struct gaainfo gaainfo;
int gaa(int argc, char **argv, gaainfo *info);
#endif /* GAA_WORKS */

int main(int argc, char **argv)
{
    gaainfo info;
    int i, v;
    if((v = gaa(argc, argv, &info)) != -1)
    {
        return 0;
    }
    printf("n : %d\nfile : %s\nverbose : %d\n", info.n, info.file, info.verbose);
    if(info.size > 0)
        for(i = 0; i < info.size; i++)
            printf("%s\n", info.input[i]);
    return 0;
}
