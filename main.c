#include "typedefs.h"
#include <stdio.h>

#include "STD_LIB.h"
#include "FILE_READ_FOR_DEBUG.h"
#include "functional_code.h"

	int32__t file_read;
	int32__t file_write;
	int32__t sys_out;
	

int main(int argc, char *argv[]){
	
	int i=0;

	FILE *fp1 = fopen(argv[1],"r");
	FILE *fp2 = fopen(argv[2],"w");
	
	static ST_LPF_PARA LPF_PARA;
	static ST_HPF_PARA HPF_PARA;
	static ST_INTE_PARA INTE_PARA;
	static ST_UNIT_DELAY DELAY_PARA;
	ST_LOOKUP_TABLE_1D LKUP_1D_PARA;

	LKUP_1D_PARA.CONST_MAP[0][0]=-300;
	LKUP_1D_PARA.CONST_MAP[0][1]=20000; // �̰͵� ���� ���� �� ������ Ÿ������ ���� OUT ���� �����ϸ��� ������ 10�� UP��Ŵ

	LKUP_1D_PARA.CONST_MAP[1][0]=-200;
	LKUP_1D_PARA.CONST_MAP[1][1]=4000;

	LKUP_1D_PARA.CONST_MAP[2][0]=300;
	LKUP_1D_PARA.CONST_MAP[2][1]=-2000;

	LKUP_1D_PARA.CONST_MAP[3][0]=400;
	LKUP_1D_PARA.CONST_MAP[3][1]=-3000;
	

	while ( i < 1001)
	{
		i++;
		file_read_for_debug(fp1);
		LPF_PARA.filt_input=file_read; // 10^2
		HPF_PARA.filt_input=file_read; // 10^2
		INTE_PARA.filt_input=file_read*SQUARE(10); // 10^2 --> ���� �������� (1/100) �� ���̱� ���ؼ� �ּ� ��ǲ�����Ͱ� ��ȿ SF�� (10^2) �̻��̾�� �ڱ�. 
		DELAY_PARA.cur_input=file_read; // 10^2
		LKUP_1D_PARA.table_input=file_read;
		

		
		//file_write=LIB_INTE(&INTE_PARA)/SQUARE(10); // 10^2
		
		//file_write=LIB_SATURATION(LIB_LOOKUP_TABLE_1D_EXTRA(&LKUP_1D_PARA,4)/10 , 100, -100);	
		functional_code(file_read);
		file_write=sys_out;
	
		file_write_for_debug(fp2);
	}



	


	fclose(fp1);
	fclose(fp2);


	



	return 0;
}

