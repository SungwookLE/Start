
#include "FILE_READ_FOR_DEBUG.h"


void file_read_for_debug(FILE *fp)
{
	// FILE *fp = fopen("____.txt","w+");
	char buffer[80];
	fgets(buffer, sizeof(buffer), fp);
	file_read=atoi(buffer);

	// fclose(fp);
	return;

}


void file_write_for_debug(FILE *fp)
{
	
	fprintf(fp,"%lld\n",file_write);
	

	// fclodse(fp);
	return;
}
