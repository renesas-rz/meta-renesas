// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2021 Renesas Electronics Corp.
 * Author: Biju Das <biju.das.jz@bp.renesas.com>
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

off_t fsize(const char *filename)
{
	struct stat st;
	if (stat(filename, &st) == 0)
		return st.st_size;
	return -1;
}

int main(int argc, char *argv[])
{
	int size, i = 0;
	char val = 0xff;
	if (argc <= 2) { /* argc should be 2 for correct execution */
		/* We print argv[0] assuming it is the program name */
		printf("usage: %s bl2_filename output_file_name\n", argv[0]);
		return -1;
	} else {
		// We assume argv[1] is a filename to open
		FILE *fptr;
		fptr = fopen(argv[2], "wb");
		/* fopen returns 0, the NULL pointer, on failure */
		if (fptr == 0)	{
			printf("Could not open file\n");
		}

		size = fsize(argv[1]);
		printf("size is %x\n",size);
		size = (size + 3) & (~0x3);
		printf("Aligned size is %x\n",size);

		fwrite(&size, 4, 1, fptr);
		for(i=0;i<506; i++)
			 fwrite(&val, 1, 1, fptr);
		val = 0x55;
		fwrite(&val, 1, 1, fptr);
		val = 0xAA;
		fwrite(&val, 1, 1, fptr);

		fclose(fptr);
	}
	return 0;
}
