/*
Main.cpp: Client for RLE.cpp compression / decompression functions

	Author: Gregory Huras
	Copyright 2019
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "RLE.h"

int main(void) {
	
	//Buffer Compression
	unsigned char myString[] = "AAAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBBBBCCCCCCCCCCCDDD";
	unsigned char myString2[] = "AAABBBCCDD";
	unsigned char outString1[140];
	unsigned char outString2[140];
	unsigned char SecondOutString[140];

	char cESC = '^';
	int inLen1, inLen2, outLen;
	inLen1 = strlen((char*)myString);
	inLen2 = strlen((char*)myString2);


	int compressedLen = RLECompress(myString, strlen((char*)myString), outString1, 140, cESC);

	printf("\nTEST STRING COMPRESSION - Compressible\n");
	printf("\nInput string: %s\n", myString);
	printf("\nInput string length: %d\n", strlen((char*)myString));
	printf("\nOutput string %s\n", outString1);
	printf("\nCompressed string length: %d\n", strlen((char*)outString1));
	printf("\nCompression Ratio: %.2f\n", (float)(compressedLen) / (float)(inLen1));

	int compressedLen2 = RLECompress(myString2, strlen((char*)myString2), outString2, 140, cESC);
	printf("\nTEST STRING COMPRESSION - Incompressible\n");
	printf("\nInput string: %s\n", myString2);
	printf("\nInput string length: %d\n", strlen((char*)myString2));
	printf("\nOutput string %s\n", outString2);
	printf("\nCompressed string length: %d\n", strlen((char*)outString2));
	printf("\nCompression Ratio: %.2f", (float)(compressedLen2) / (float)(inLen2));
	
	RLEdeCompress(outString1, strlen((char*)outString1), SecondOutString, 140, cESC);
	printf("\nTEST STRING DECOMPRESSION\n");
	printf("\nOutput string %s\n", SecondOutString);

	// File Compression
	printf("\n\nFILE COMPRESSION\n");

	FILE* fptr1 = NULL;							// File pointer for input decompressed file
	FILE* fptr2 = NULL;							// File pointer for input compressed file
	char name1[] = ".\\Debug\\Thing.txt";		// Input decompressed file
	char name2[] = ".\\Debug\\Thing2.txt";		// Input compressed file
	char* fileOut1;								// Location to write compressed string from decompressed file
	char* fileOut2;								// Location to write decompressed string from compressed file
	int fileLen1 = 0;							// Length of input decompressed file
	int fileLen2 = 0;							// Length of input compressed file
	int fileOutLen1 = 0;						// Length of output compressed file
	int fileOutLen2 = 0;						// Length of output decompressed file

	fptr1 = fopen((const char*)name1, "r");
	fptr2 = fopen((const char*)name2, "r");

	if (fptr1 == NULL) {
		printf("\nFailed to open file");
		fclose(fptr1);
		return(0);
	}
	if (fptr2 == NULL) {
		printf("\nFailed to open compressed file");
		fclose(fptr2);
		return(0);
	}

	while (fgetc(fptr1) != EOF) {
		fileLen1++;								// Length of the decompressed input file
	}
	while (fgetc(fptr2) != EOF) {
		fileLen2++;								// Length of the compressed input file
	}
	fileOut1 = (char*)malloc(fileLen1);			// Allocate memory
	fileOut2 = (char*)malloc(fileLen2*10);		// Allocate memory

	fileOutLen1 = fileRLECompress(fptr1, fileLen1, fileOut1, cESC);
	fclose(fptr1);

	printf("Input file length: %d", fileLen1);
	printf("\nOutput file:\n%s\n", fileOut1);
	printf("\nCompressed string length: %d\n", fileOutLen1);
	printf("\nCompression Ratio: %.4f\n", (float)fileOutLen1 / (float)fileLen1);

	fileRLEdeCompress(fptr2, fileLen2, fileOut2, cESC);
	printf("\nOutput string:\n%s\n", fileOut2);
	fclose(fptr2);

	return(0);
}