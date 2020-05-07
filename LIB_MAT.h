#ifndef _LIB_MAT_H_
#define _LIB_MAT_H_

    #include "typedef.h"
    #define ABS(A) (A)>0 ? (A):(-A)
    #define MAX(A,B) A>B? (A):(B)
    #define MIN(A,B) A>B? (B):(A)

    typedef struct{
        int32_t flt_input;
        int32_t out;
    }LPF_PARA;

    int32_t LIB_LPF(LPF_PARA *LPF_ST, int32_t tau, int32_t res);




#endif