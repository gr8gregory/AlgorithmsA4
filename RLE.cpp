/*
RLE.cpp: Implimentation of RLE compression / decompression functions for string processing

	Author: Gregory Huras, Caleb Hoeksema, Laura Muhlbauerova
	Copyright 2019
*/
#pragma warning (disable: 4996)

// Header Files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// String Compression Function
int RLECompress(unsigned char* in, int iInLen, unsigned char* out, int iOutMax, unsigned char cESC) {

	unsigned char charac;		// Repeated character
	unsigned char output[10];	// Temp buffer with space for the RLE sequence
	out[0] = '\0';				// Set so that we can use strcat()
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
		if (count > 3) {												// Enode the output
			sprintf((char*)output, "%c%02x%c", cESC, count, charac);	// Copy to a temporary buffer
			strcat((char*)out, (char*)output);							// Append temporary buffer to output buffer

		}
		else if (count == 3) {											// Don't encode
			sprintf((char*)output, "%c%c%c", charac, charac, charac);
			strcat((char*)out, (char*)output);
		}
		else if (count == 2) {											// Don't encode
			sprintf((char*)output, "%c%c", charac, charac);
			strcat((char*)out, (char*)output);
		}
		else if (count == 1) {											// Don't encode
			output[0] = in[i];											// Copy the character to the output
			output[1] = '\0';											// Add NULL terminator for concatenation
			strcat((char*)out, (char*)output);
		}
		i++;															// Step the counter to move to the next character
		
	}
	return(strlen((char*)out));											// Return the size of the output

}


// String Decompression Function
int RLEdeCompress(unsigned char* in, int iInLen, unsigned char* out, int iOutMax, unsigned char cESC) {

	char num[3];								// Memory to store the number of repeated characters
	char Let;									// Holds the letter to repeat
	int dec;									// Holds decimal conversion of repeated numbers
	unsigned char* charp = out;					// Character pointer for decoding so the start of the array is not lost

	for (int i = 0; i < iInLen; i++) {

		if (in[i] == cESC) {
			num[0] = in[i + 1];					// First digit
			num[1] = in[i + 2];					// Second digit
			num[2] = '\0';
			Let = in[i + 3];					// The repeated letter
			
			dec = (int)strtol(num, NULL, 16);	// Convert to decimal

			for (int j = 0; j < dec; j++) {		// Repeat as specified
				*charp = Let;
				charp++;
			}
			i = i + 3;							// Step past the current repeat sequence
		}
		else {									// If no escape character
			*charp = in[i];
			charp++;
		}
	}
	charp[0] = '\0';							// Null terminate the string

	return 0;
}