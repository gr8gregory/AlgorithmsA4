/*
fileRLE.cpp: Implimentation of RLE compression / decompression functions for file processing

	Author: Gregory Huras, Caleb Hoeksema, Laura Muhlbauerova
	Copyright 2019
*/
#pragma warning (disable: 4996)

// Header Files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "RLE.h"


// File Compression Function
int fileRLECompress(FILE* fp, int fileLen, char* fileout, unsigned char cESC) {

	char* charp = fileout;			// File pointer to prevent losing fileout's location
	int size = 0;					// Store the size of the output file

	fseek(fp, 0, SEEK_SET);			// From the start
	while (fgetc(fp) != EOF) {
		fseek(fp, -1, SEEK_CUR);	// Move back since fgetc in the previous line stepped the file pointer
		*charp = fgetc(fp);			// Store the input
		charp++;
	}
	charp = fileout;				// Reset the pointer's location for passing out
	charp[fileLen] = '\0';			// Terminate properly

	size = RLECompress((unsigned char*)charp, fileLen, (unsigned char*)fileout, fileLen, cESC);	// Compress
	return(size);
}

// File Decompression Function	
int fileRLEdeCompress(FILE* fp, int fileLen, char* fileout, unsigned char cESC) {

	char* input = (char*)malloc(fileLen);	// File pointer to prevent losing fileout's location
	char* charp = input;					// Temporary pointer so start of array is not lost

	fseek(fp, 0, SEEK_SET);					// From the start
	while (fgetc(fp) != EOF) {
		fseek(fp, -1, SEEK_CUR);			// Move back because of fgetc in previous line
		*input = fgetc(fp);
		input++;
	}
	input = charp;							// Reset the pointer's location
	input[fileLen] = '\0';					// Terminate properly

	RLEdeCompress((unsigned char*)charp, fileLen, (unsigned char*)fileout, fileLen, cESC);	// Decompress
	return(0);
}

