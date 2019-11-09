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
	unsigned char outString[140];
	unsigned char SecondOutString[140];

	char cESC = '^';
	int inLen1, inLen2, outLen;
	inLen1 = strlen((char*)myString);
	inLen2 = strlen((char*)myString2);


	int compressedLen = RLECompress(myString, strlen((char*)myString), outString, 140, cESC);

	printf("\nInput string: %s\n", myString);
	printf("\nInput string length: %d\n", strlen((char*)myString));
	printf("\nOutput string %s\n", outString);
	printf("\nCompressed string length: %d\n", strlen((char*)outString));
	printf("\nCompression Ratio: %.2f\n", (float)(compressedLen) / (float)(inLen1));

	/*int compressedLen2 = RLECompress(myString2, strlen((char*)myString2), outString, 140, cESC);
	printf("\nInput string: %s\n", myString2);
	printf("\nInput string length: %d\n", strlen((char*)myString2));
	printf("\nOutput string %s\n", outString);
	printf("\nCompressed string length: %d\n", strlen((char*)outString));
	printf("\nCompression Ratio: %.2f", (float)(compressedLen2) / (float)(inLen2));
	*/
	RLEdeCompress(outString, strlen((char*)outString), SecondOutString, 140, cESC);
	printf("\nOutput string %s\n", SecondOutString);

	printf("\n\nFILE COMPRESSION\n");
	//File Compression
	FILE* fptr = NULL;
	errno_t err;
	char c;
	int counter = 0;
	char userIn[80] = "C:\\Users\\caleb\\Documents\\GitHub\\AlgorithmsA4\\AlgorithmsA4\\Debug\\Thing.txt";
	int fileLen = 0;
	int fileCompLen = 0;

	/*printf("\nEnter a file to compress: ");
	scanf_s("%79s", userIn, sizeof(userIn));
	userIn[strlen(userIn)] = '\0';*/

	fptr = fopen((const char*)userIn, "r");

	if (fptr == NULL) {
		printf("\nFailed to open file");
		fclose(fptr);
		return(0);
	}

	while ((c = fgetc(fptr)) != EOF) {
		fileLen++;											//counts the length of the file
	}
	char *fileOut = (char*)malloc(fileLen);

	fileCompLen = fileRLECompress(fptr, fileLen, fileOut, cESC);
	fclose(fptr);												// don't need the file in main anymore

	printf("Input file length: %d", fileLen);
	printf("\nOutput file: %s\n", fileOut);
	printf("\nCompressed string length: %d\n", strlen((char*)fileOut));
	printf("\nCompression Ratio: %.2f\n", (float)strlen(fileOut) / (float)fileLen);

	return(0);
}