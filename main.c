#include <stdio.h>
#include "LIB_MAT.h"

int main(int argc, char *argv)
{
    static LPF_PARA LPF_TEST;
    int i=0;
    int32_t j=0;

    printf("FIRST STEP TO GIT SUB!!\n");
    
    while(1)
    {
        LPF_TEST.flt_input = i++;
        j=LIB_LPF(&LPF_TEST, 10,1);

        printf("[%d]out test value is %lld \n",i,j);

        if (i>10)
            break;

    }

    return 0;
}