#include "LIB_MAT.h"

int32_t LIB_LPF(LPF_PARA *LPF_ST, int32_t tau, int32_t res){

    int32_t outRes;

    outRes=LPF_ST->out+tau-res;
    outRes = outRes + LPF_ST->flt_input;
    


    return outRes;
}