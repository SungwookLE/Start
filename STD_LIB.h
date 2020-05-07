#ifndef _STD_LIB_H_
#define _STD_LIB_H_

#include "typedefs.h"
#include <math.h>

/* 
@ AUTHOR	  : Sungwook LEE (sungwook.Lee@hyundai.com)
@ DATA		  : '20.03.27
@ DESCRIPTION : STANDARD MATLAB SIMULINK LIBRARY FUNCTION

@ LIST OF FUNCTION

0. ABS
1. MAX
2. MIN
3. SQUARE
4. LPF
5. HPF
6. INTEGRATOR : ��ȿ���ڿ����� ���еʿ� ���� ���� ���� ���� Ʋ��.
7. UNIT DELAY 
8. 1D LOOKUP_TABLE : 2�� (CLIPPING / Linear EXTRAPOLATION)
TIP: ���� ����� �� ��ȿ���� ������ ���� ��Ȯ���� ������ �� �����Ƿ� SCALE �� ����� ��
9. SATURATION


-- �� --
10. 2D LOOKUP_TABLE : 2D ����� �ʿ��ұ�.. �������� ���� ���µ�.. �̰� ���� �� ���鋚�� �׷��� ��õ�ϴ� ����� �ƴϾ����
11. PRODUCT (HIGH PRECISION -> �̰� ��Ȯ�� ���� �ǹ����� �ľ��ؾ� �� 200405)
12. DIVIDE (HIGH PRECISION -> �̰� ��Ȯ�� ���� �ǹ����� �ľ��ؾ� �� 200405)
*/
	
#define ABS(A) A>=0? A:(-A)
#define MIN(A,B) A>B?B:A 
#define MAX(A,B) A>B?A:B
#define SQUARE(A) (A*A)

typedef struct{
	int32_t filt_input;
	int32_t filt_output;
}ST_LPF_PARA;

typedef struct{
	int32_t filt_input;
	int32_t filt_output;
	int32_t temp;
}ST_HPF_PARA;

typedef struct{
	int32_t filt_input;
	int32_t filt_output;
}ST_INTE_PARA;

typedef struct{
	int32_t cur_input;
	int32_t ex_value;
	int32_t ex_output;
}ST_UNIT_DELAY;

typedef struct{
	int32_t table_input;
	int32_t table_output;
	int32_t CONST_MAP[100][2];
}ST_LOOKUP_TABLE_1D;

/*	@ FUNCTION NAME: 1. LOW PASS FILTER
	@ DATE         : '20.03.27
	@ DESCRIPTION  : RES/TAU must be 10^-2 for 10ms LOOP */
int32_t LIB_LPF(ST_LPF_PARA *LPF_PARA,int16_t TAU,int16_t RES);
/*	@ FUNCTION NAME: 2. HIGH PASS FILTER
	@ DATE         : '20.03.27
	@ DESCRIPTION  : RES/TAU must be 10^2 for 10ms LOOP */
int32_t LIB_HPF(ST_HPF_PARA *HPF_PARA,int16_t TAU,int16_t RES);
/*	@ FUNCTION NAME: 3. INTEGRATOR
	@ DATE         : '20.03.27
	@ DESCRIPTION  : It works for 10ms LOOP */
int32_t LIB_INTE(ST_INTE_PARA *INTE_PARA);
/*	@ FUNCTION NAME: 4. UNIT DELAY
	@ DATE         : '20.03.27
	@ DESCRIPTION  : It works for 10ms LOOP */
int32_t LIB_UNIT_DELAY(ST_UNIT_DELAY *DELAY_PARA);
/*	@ FUNCTION NAME: 1D LOOKUP_TABLE Using CLIPPING OPTION
	@ DATE         : '20.03.27
	@ DESCRIPTION  : It works for 1D LOOK UP CLIPPING OPTION  */
int32_t LIB_LOOKUP_TABLE_1D_CLIP(ST_LOOKUP_TABLE_1D *LOOKUP_1D, int16_t size_of_map);
/*	@ FUNCTION NAME: 1D LOOKUP_TABLE Using extrapolation OPTION
	@ DATE         : '20.03.27
	@ DESCRIPTION  : It works for 1D LOOK UP LINEAR EXTRAPOLATION */
int32_t LIB_LOOKUP_TABLE_1D_EXTRA(ST_LOOKUP_TABLE_1D *LOOKUP_1D, int16_t size_of_map);
/*	@ FUNCTION NAME: SATURATION
	@ DATE         : '20.04.04
	@ DESCRIPTION  : Upper Under Bound works */
int32_t LIB_SATURATION(int32_t input, int32_t upper, int32_t under);

#endif

