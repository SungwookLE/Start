#include "functional_code.h"



void functional_code(int32_t func_in)
{

	int32_t temp_gain, temp_lookup, temp_sum;
	static int32_t pre_val;
	ST_LOOKUP_TABLE_1D LKUP_1D_PARA;
	static ST_LPF_PARA SYSTEM_PARA;
	

	LKUP_1D_PARA.CONST_MAP[0][0]=-300;
	LKUP_1D_PARA.CONST_MAP[0][1]=20000; // 이것도 기울기 구할 때 데이터 타입으로 인해 OUT 쪽의 스케일링을 강제로 10배 UP시킴

	LKUP_1D_PARA.CONST_MAP[1][0]=-200;
	LKUP_1D_PARA.CONST_MAP[1][1]=4000;

	LKUP_1D_PARA.CONST_MAP[2][0]=300;
	LKUP_1D_PARA.CONST_MAP[2][1]=-2000;

	LKUP_1D_PARA.CONST_MAP[3][0]=400;
	LKUP_1D_PARA.CONST_MAP[3][1]=-3000;

	temp_gain=LIB_SATURATION(func_in, 200, -200) * 0.4;  // SF: 10^2
	LKUP_1D_PARA.table_input = temp_gain;
	temp_lookup = LIB_LOOKUP_TABLE_1D_EXTRA(&LKUP_1D_PARA,4)/10; // SF: 10^2
	
	// pre_val is delayed "ouput"
	temp_sum=temp_lookup-pre_val;
	SYSTEM_PARA.filt_input=40*temp_sum;
	sys_out=LIB_LPF(&SYSTEM_PARA, 100, 1);
	pre_val=sys_out;

	return;
}
