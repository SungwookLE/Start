#include "STD_LIB.h"

/*	@ AUTHOR	  : Sungwook LEE (sungwook.Lee@hyundai.com)
	@ DESCRIPTION : STANDARD MATLAB SIMULINK LIBRARY FUNCTION */

/*	@ FUNCTION NAME: LOW PASS FILTER
	@ DATE         : '20.03.27
	@ DESCRIPTION  : RES/TAU must be 10^-2 for 10ms LOOP */
int32__t LIB_LPF(ST_LPF_PARA *LPF_PARA,int16__t TAU,int16__t RES)
{
	if (TAU==0) // DEFENCE DIVIDE ZERO
		LPF_PARA->filt_output=LPF_PARA->filt_input;
	else
		LPF_PARA->filt_output=(LPF_PARA->filt_input- LPF_PARA->filt_output)*RES/TAU+LPF_PARA->filt_output ;

	return LPF_PARA->filt_output;
}

/*	@ FUNCTION NAME: HIGH PASS FILTER
	@ DATE         : '20.03.27
	@ DESCRIPTION  : RES/TAU must be 10^2 for 10ms LOOP */
int32__t LIB_HPF(ST_HPF_PARA *HPF_PARA,int16__t TAU,int16__t RES)
{
	HPF_PARA->filt_output = (TAU*HPF_PARA->temp/(TAU+RES) + TAU*HPF_PARA->filt_input/(TAU+RES));
	HPF_PARA->temp = HPF_PARA->filt_output - HPF_PARA->filt_input;
	
	return HPF_PARA->filt_output;
}

/*	@ FUNCTION NAME: INTEGRATOR
	@ DATE         : '20.03.27
	@ DESCRIPTION  : It works for 10ms LOOP */
int32__t LIB_INTE(ST_INTE_PARA *INTE_PARA)
{
	INTE_PARA->filt_output=(INTE_PARA->filt_input)*1/100+INTE_PARA->filt_output ;
	// ���е� ���� ������ ���� ���п����� �����ϳ�.. �̷��� �����ϸ� ������.

	return INTE_PARA->filt_output;
}

/*	@ FUNCTION NAME: UNIT DELAY
	@ DATE         : '20.03.27
	@ DESCRIPTION  : It works for 10ms LOOP */
int32__t LIB_UNIT_DELAY(ST_UNIT_DELAY *DELAY_PARA)
{
	DELAY_PARA->ex_output=DELAY_PARA->ex_value;
	DELAY_PARA->ex_value=DELAY_PARA->cur_input;

	return DELAY_PARA->ex_output;
}

/*	@ FUNCTION NAME: 1D LOOKUP_TABLE Using CLIPPING OPTION
	@ DATE         : '20.03.27
	@ DESCRIPTION  : It works for 1D LOOK UP CLIPPING OPTION  */
int32__t LIB_LOOKUP_TABLE_1D_CLIP(ST_LOOKUP_TABLE_1D *LOOKUP_1D, int16__t size_of_map)
{

	/*	X-axis: input
		Y-axis: output --> ONE TO ONE MATCHING */ 
	int16__t start = 0;
	int16__t end = size_of_map-1;
	int16__t mid;

	int16__t input_MIN = LOOKUP_1D->CONST_MAP[0][0];
	int16__t input_MAX = LOOKUP_1D->CONST_MAP[end][0];

	if (LOOKUP_1D->table_input <= input_MIN)
	{ // input MIN bound:: FLAT
		LOOKUP_1D->table_output = LOOKUP_1D->CONST_MAP[0][1];
	}
	else if (LOOKUP_1D->table_input >= input_MAX )
	{ // input MAX bound:: FLAT
		LOOKUP_1D->table_output = LOOKUP_1D->CONST_MAP[end][1];
	}
	else
	{ // input in bound :: find the specific interval using BINARY SEARCH	
		while(start <= end)
		{	mid= (start+end)/2;
			if (LOOKUP_1D->table_input < LOOKUP_1D->CONST_MAP[mid][0])
			{ // LEFT WING
				end=mid-1;
			}
			else if (LOOKUP_1D->CONST_MAP[mid][0] < LOOKUP_1D->table_input)
			{ // RIGHT WING
				start=mid+1;
			}
			else
				break;
		}

		if (mid==0)
		{
			LOOKUP_1D->table_output = (LOOKUP_1D->CONST_MAP[mid+1][1]-LOOKUP_1D->CONST_MAP[mid][1])/(LOOKUP_1D->CONST_MAP[mid+1][0]-LOOKUP_1D->CONST_MAP[mid][0])*(LOOKUP_1D->table_input-LOOKUP_1D->CONST_MAP[mid][0])+LOOKUP_1D->CONST_MAP[mid][1];
		}
		else
		{
			LOOKUP_1D->table_output = (LOOKUP_1D->CONST_MAP[mid][1]-LOOKUP_1D->CONST_MAP[mid-1][1])/(LOOKUP_1D->CONST_MAP[mid][0]-LOOKUP_1D->CONST_MAP[mid-1][0])*(LOOKUP_1D->table_input-LOOKUP_1D->CONST_MAP[mid-1][0])+LOOKUP_1D->CONST_MAP[mid-1][1];
		}
	}

	return LOOKUP_1D->table_output;
}

/*	@ FUNCTION NAME: 1D LOOKUP_TABLE Using extrapolation OPTION
	@ DATE         : '20.03.27
	@ DESCRIPTION  : It works for 1D LOOK UP LINEAR EXTRAPOLATION */
int32__t LIB_LOOKUP_TABLE_1D_EXTRA(ST_LOOKUP_TABLE_1D *LOOKUP_1D, int16__t size_of_map)
{

	/*	X-axis: input
		Y-axis: output --> ONE TO ONE MATCHING */ 
	int16__t start = 0;
	int16__t end = size_of_map-1;
	int16__t mid;

	int16__t input_MIN = LOOKUP_1D->CONST_MAP[0][0];
	int16__t input_MAX = LOOKUP_1D->CONST_MAP[end][0];

	if (LOOKUP_1D->table_input <= input_MIN)
	{ // input MIN bound:: EXTRA
		LOOKUP_1D->table_output = (LOOKUP_1D->CONST_MAP[start+1][1]-LOOKUP_1D->CONST_MAP[start][1])/(LOOKUP_1D->CONST_MAP[start+1][0]-LOOKUP_1D->CONST_MAP[start][0])*(LOOKUP_1D->table_input-LOOKUP_1D->CONST_MAP[start][0])+LOOKUP_1D->CONST_MAP[start][1];
	}
	else if (LOOKUP_1D->table_input >= input_MAX )
	{ // input MAX bound:: EXTRA
		LOOKUP_1D->table_output = (LOOKUP_1D->CONST_MAP[end][1]-LOOKUP_1D->CONST_MAP[end-1][1])/(LOOKUP_1D->CONST_MAP[end][0]-LOOKUP_1D->CONST_MAP[end-1][0])*(LOOKUP_1D->table_input-LOOKUP_1D->CONST_MAP[end][0])+LOOKUP_1D->CONST_MAP[end][1];
	}
	else
	{ // input in bound :: find the specific interval using BINARY SEARCH	
		while(start <= end)
		{	mid= (start+end)/2;
			if (LOOKUP_1D->table_input < LOOKUP_1D->CONST_MAP[mid][0])
			{ // LEFT WING
				end=mid-1;
			}
			else if (LOOKUP_1D->CONST_MAP[mid][0] < LOOKUP_1D->table_input)
			{ // RIGHT WING
				start=mid+1;
			}
			else
				break;
		}

		if (mid==0)
		{
			LOOKUP_1D->table_output = (LOOKUP_1D->CONST_MAP[mid+1][1]-LOOKUP_1D->CONST_MAP[mid][1])/(LOOKUP_1D->CONST_MAP[mid+1][0]-LOOKUP_1D->CONST_MAP[mid][0])*(LOOKUP_1D->table_input-LOOKUP_1D->CONST_MAP[mid][0])+LOOKUP_1D->CONST_MAP[mid][1];
		}
		else
		{
			LOOKUP_1D->table_output = (LOOKUP_1D->CONST_MAP[mid][1]-LOOKUP_1D->CONST_MAP[mid-1][1])/(LOOKUP_1D->CONST_MAP[mid][0]-LOOKUP_1D->CONST_MAP[mid-1][0])*(LOOKUP_1D->table_input-LOOKUP_1D->CONST_MAP[mid-1][0])+LOOKUP_1D->CONST_MAP[mid-1][1];
		}
	}

	return LOOKUP_1D->table_output;
}

/*	@ FUNCTION NAME: SATURATION
	@ DATE         : '20.04.04
	@ DESCRIPTION  : Upper Under Bound works */
int32__t LIB_SATURATION(int32__t input, int32__t upper, int32__t under)
{
	int32__t output;
	input > upper? (output=upper):(input < under? (output=under):(output=input));
	return output;
}








	