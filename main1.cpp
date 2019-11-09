/*
Main.cpp: Client for RLE.cpp compression / decompression functions

	Author: Gregory Huras
	Copyright 2019
*/
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


	//File Compression
	FILE* fp;
	errno_t err;
	FILE* fout;
	char c;
	int counter = 0;
	char userIn[80];
	char filenameIn[82] = "./";
	char filenameOut[84] = "Comp";
	int fileLen = 0;
	int fileCompLen = 0;
//	char* fileOut;

	printf("\nEnter a file to compress: ");
	scanf_s("%79s", userIn, sizeof(userIn));
	strcat_s(filenameIn, sizeof(userIn) + 2, userIn);
	//printf("%s", filenameIn);

	if (err = fopen_s(&fp, userIn, "r") == 1) {
		printf("\nFailed to open the file\n");
		fclose(fp);
		return(0);
	}

	//userIn[strlen(userIn) - 1] = '\0';
	strcat_s(filenameOut, sizeof(userIn)+4, userIn);
	//printf("%s", filenameOut);

	if (err = fopen_s(&fout, filenameOut, "w") == 1) {
		printf("\nFailed to open the file\n");
		fclose(fout);
		return(0);
	}

	while ((c = fgetc(fp)) != EOF) {
		fileLen++;											//counts the length of the file
	}

	fileRLECompress(fp, fileLen, fout, cESC);
	fclose(fp);												// don't need the file in main anymore
	


	return(0);
}