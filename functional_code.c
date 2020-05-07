#include "functional_code.h"



void functional_code(int32__t func_in)
{

	int32__t temp_gain, temp_lookup, temp_sum;
	static int32__t pre_val;
	ST_LOOKUP_TABLE_1D LKUP_1D_PARA;
	static ST_LPF_PARA SYSTEM_PARA;
	

	LKUP_1D_PARA.CONST_MAP[0][0]=-300;
	LKUP_1D_PARA.CONST_MAP[0][1]=20000; // �̰͵� ���� ���� �� ������ Ÿ������ ���� OUT ���� �����ϸ��� ������ 10�� UP��Ŵ

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
