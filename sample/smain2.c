/* main file corresponding to sample2.gaa */
#include <stdio.h>
#include "sample2_gaa.h"

int main(int argc, char **argv)
{
    gaainfo info;
    int i, v;
    if((v = gaa_file("config", &info)) != -1) 
		/* gets options from file 'config' */
    {
        return 0;
    }
    if((v = gaa(argc, argv, &info)) != -1)
    {
        return 0;
    } 
    printf("n : %d\nm : %d\nfile nf : %s %d\nverbose : %d\n",
           info.n, info.m, info.file,info.nf , info.verbose);
    if(info.size > 0)
        for(i = 0; i < info.size; i++)
            printf("%s\n", info.input[i]);
    return 0;
}
