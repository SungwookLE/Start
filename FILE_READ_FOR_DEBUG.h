#ifndef _FILE_READ_FOR_DEBUG_H_
#define _FILE_READ_FOR_DEBUG_H_

#include "typedefs.h"
#include <stdio.h>
#include <stdlib.h>

	extern int32__t file_read;
	extern int32__t file_write;

	void file_read_for_debug(FILE *fp);
	void file_write_for_debug(FILE *fp);


#endif