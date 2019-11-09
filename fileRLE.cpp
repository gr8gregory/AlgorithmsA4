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

	char* fileCont;
	char c;

	unsigned char charac;		// Repeated character
	unsigned char output[10];	// Temp buffer with space for the RLE sequence
	fileout[0] = '\0';				// Set so that we can use strcat()
	int i = 0;					// Counter
	int count;					// Number of repeats
	int temp = 0;
	
	fseek(fp, 1, SEEK_SET);
	while ((c = fgetc(fp)) != EOF) {		// Dont want to exceed the buffer

		count = 1;				// Starts the count of a set
		while ((c == fgetc(fp)) && (fgetc(fp) != EOF)) {	// While there are repeated characters, increment the counter
			fseek(fp, -1, SEEK_CUR);					// Back up one character to compare with it
			charac = c;		// Save the repeated character 
			count++;
			i++;
			temp++;
		}
		fseek(fp, -1, SEEK_CUR);
		if ((c != fgetc(fp)) && (fgetc(fp) != EOF)) {
			//move back
			fseek(fp, -2, SEEK_CUR);
		}
		// if they did match, the file pointer is already in the right spot


		// Encode the output
		if (count > 3) {
			// RLE encode 
			// copt to temp buffer
			sprintf((char*)output, "%c%02x%c", cESC, count, charac);
			// Copy temp buffer to output buffer
			strcat((char*)fileout, (char*)output);

		}
		else if (count == 3) {
			// Dont encode
			sprintf((char*)output, "%c%c%c", charac, charac, charac);
			strcat((char*)fileout, (char*)output);
		}
		else if (count == 2) {
			// Dont encode
			sprintf((char*)output, "%c%c", charac, charac);
			strcat((char*)fileout, (char*)output);
		}
		else if (count == 1) {
			output[0] = c;
			output[1] = '\0';
			strcat((char*)fileout, (char*)output);
		}
		i++;

	}
	return(strlen((char*)fileout));

}
/*
int RLEdeCompress(unsigned char* in, int iInLen, unsigned char* out, int iOutMax, unsigned char cESC) {
	char num[3];
	char Let;
	int number;
	int dec;
	int inc = 0;

	for (int i = 0; i < iInLen; i++) {

		if (in[i] == cESC) {
			num[0] = in[i + 1];
			num[1] = in[i + 2];
			num[2] = '\0';
			Let = in[i + 3];
			number = (int)num[0] * 16 + (int)num[1];

			dec = (int)strtol(num, NULL, 16);

			for (int j = 0; j < dec; j++)
			{
				//printf("%c", Let);
				*out = Let;
				out++;
				inc++;
			}
			number = 0;
			i = i + 3;
		}
		else
		{
			*out = in[i];
			out++;
			inc++;
		}
	}
	out[0] = '\0';

	return 0;
}*/