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
TIP: ���� ����� �� ��ȿ���� ������ ���� ��Ȯ���� ������ �� �����Ƿ� SCALE �� ������ ��
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
	int32__t filt_input;
	int32__t filt_output;
}ST_LPF_PARA;

typedef struct{
	int32__t filt_input;
	int32__t filt_output;
	int32__t temp;
}ST_HPF_PARA;

typedef struct{
	int32__t filt_input;
	int32__t filt_output;
}ST_INTE_PARA;

typedef struct{
	int32__t cur_input;
	int32__t ex_value;
	int32__t ex_output;
}ST_UNIT_DELAY;

typedef struct{
	int32__t table_input;
	int32__t table_output;
	int32__t CONST_MAP[100][2];
}ST_LOOKUP_TABLE_1D;

/*	@ FUNCTION NAME: 1. LOW PASS FILTER
	@ DATE         : '20.03.27
	@ DESCRIPTION  : RES/TAU must be 10^-2 for 10ms LOOP */
int32__t LIB_LPF(ST_LPF_PARA *LPF_PARA,int16__t TAU,int16__t RES);
/*	@ FUNCTION NAME: 2. HIGH PASS FILTER
	@ DATE         : '20.03.27
	@ DESCRIPTION  : RES/TAU must be 10^2 for 10ms LOOP */
int32__t LIB_HPF(ST_HPF_PARA *HPF_PARA,int16__t TAU,int16__t RES);
/*	@ FUNCTION NAME: 3. INTEGRATOR
	@ DATE         : '20.03.27
	@ DESCRIPTION  : It works for 10ms LOOP */
int32__t LIB_INTE(ST_INTE_PARA *INTE_PARA);
/*	@ FUNCTION NAME: 4. UNIT DELAY
	@ DATE         : '20.03.27
	@ DESCRIPTION  : It works for 10ms LOOP */
int32__t LIB_UNIT_DELAY(ST_UNIT_DELAY *DELAY_PARA);
/*	@ FUNCTION NAME: 1D LOOKUP_TABLE Using CLIPPING OPTION
	@ DATE         : '20.03.27
	@ DESCRIPTION  : It works for 1D LOOK UP CLIPPING OPTION  */
int32__t LIB_LOOKUP_TABLE_1D_CLIP(ST_LOOKUP_TABLE_1D *LOOKUP_1D, int16__t size_of_map);
/*	@ FUNCTION NAME: 1D LOOKUP_TABLE Using extrapolation OPTION
	@ DATE         : '20.03.27
	@ DESCRIPTION  : It works for 1D LOOK UP LINEAR EXTRAPOLATION */
int32__t LIB_LOOKUP_TABLE_1D_EXTRA(ST_LOOKUP_TABLE_1D *LOOKUP_1D, int16__t size_of_map);
/*	@ FUNCTION NAME: SATURATION
	@ DATE         : '20.04.04
	@ DESCRIPTION  : Upper Under Bound works */
int32__t LIB_SATURATION(int32__t input, int32__t upper, int32__t under);

#endif

