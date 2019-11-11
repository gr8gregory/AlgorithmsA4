/*
fileRLE.cpp: Implimentation of RLE compression / decompression functions for files

	Author: Gregory Huras
	Copyright 2019
*/
#pragma warning (disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "RLE.h"

int fileRLECompress(FILE* fp, int fileLen, char* fileout, unsigned char cESC) {

	char* charp = fileout;			// File pointer to prevent losing fileout's location
	int size = 0;					// store the size of the output file

	fseek(fp, 0, SEEK_SET);
	while (fgetc(fp) != EOF) {
		fseek(fp, -1, SEEK_CUR);
		*charp = fgetc(fp);
		charp++;
	}
	charp = fileout;				// Reset the pointer's location
	charp[fileLen] = '\0';			// Terminate properly

	size = RLECompress((unsigned char*)charp, fileLen, (unsigned char*)fileout, fileLen, cESC); // Compress
	return(size);
}
	
int fileRLEdeCompress(FILE* fp, int fileLen, char* fileout, unsigned char cESC) {

	char* input = (char*)malloc(fileLen);			// File pointer to prevent losing fileout's location
	char* charp = input;

	fseek(fp, 0, SEEK_SET);
	while (fgetc(fp) != EOF) {
		fseek(fp, -1, SEEK_CUR);
		*input = fgetc(fp);
		input++;
	}
	input = charp;				// Reset the pointer's location
	input[fileLen] = '\0';			// Terminate properly
	printf("Compressed thing to Decompress:\n%s\n", charp);
	RLEdeCompress((unsigned char*)charp, fileLen, (unsigned char*)fileout, fileLen, cESC); // Decompress
	return(0);
}

