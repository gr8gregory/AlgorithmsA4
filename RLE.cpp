/*
RLE.cpp: Implimentation of RLE compression / decompression functions

	Author: Gregory Huras
	Copyright 2019
*/
#pragma warning (disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int RLECompress(unsigned char* in, int iInLen, unsigned char* out, int iOutMax, unsigned char cESC) {

	unsigned char charac;		// Repeated character
	unsigned char output[10];	// Temp buffer with space for the RLE sequence
	out[0] = '\0';				// Set so taht we can use strcat()
	int i = 0;					// Counter
	int count;					// Number of repeats

	while (i < iInLen) {		// Dont want to exceed the buffer

		count = 1;				// Starts the count of a set
		while ((in[i] == in[i+1]) && (i< iInLen)) {	// While there are repeated characters, increment the counter

			charac = in[i];		// Save the repeated character 
			count++;
			i++;
		}
		
		// Encode the output
		if (count > 3) {
			// RLE encode 
			// copt to temp buffer
			sprintf((char*)output, "%c%02x%c", cESC, count, charac);
			// Copy temp buffer to output buffer
			strcat((char*)out, (char*)output);

		}
		else if (count == 3) {
			// Dont encode
			sprintf((char*)output, "%c%c%c", charac, charac, charac);
			strcat((char*)out, (char*)output);
		}
		else if (count == 2) {
			// Dont encode
			sprintf((char*)output, "%c%c", charac, charac);
			strcat((char*)out, (char*)output);
		}
		else if (count == 1) {
			output[0] = in[i];
			output[1] = '\0';
			strcat((char*)out, (char*)output);
		}
		i++;
		
	}
	return(strlen((char*)out));

}

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
			number = (int)num[0]*16 + (int)num[1];
			
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
}