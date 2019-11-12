/*
Main.cpp: Client for RLE.cpp compression / decompression functions

	Author: Gregory Huras, Caleb Hoeksema, Laura Muhlbauerova
	Copyright 2019
*/

#define _CRT_SECURE_NO_WARNINGS

// Header Files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "RLE.h"


// Testing mainline for RLE Compression
//		The fuction is split into 2 sections (including variable declarations)
int main(void) {
	
	// STRING COMPRESSION
	unsigned char CompStr[] = "AAAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBBBBCCCCCCCCCCCDDD";		// Compressible string
	unsigned char IncompStr[] = "AAABBBCCDD";													// Incompressible string
	unsigned char outString1[140];																// Output string from compressible string
	unsigned char outString2[140];																// Output string from incompressible string
	unsigned char DecompStr[140];																// Output string after decompression
	char cESC = '^';																			// Escape sequence
	int inLen1, inLen2, compressedLen1, compressedLen2;									// Store string lengths

	inLen1 = strlen((char*)CompStr);															// Length of compressible string
	inLen2 = strlen((char*)IncompStr);															// Length of incompressible string
	
	compressedLen1 = RLECompress(CompStr, strlen((char*)CompStr), outString1, 140, cESC);		// Compress compressible string
	compressedLen2 = RLECompress(IncompStr, strlen((char*)IncompStr), outString2, 140, cESC);	// "Compress" incompressible string

	// Compressible String Results
	printf("\nTEST STRING COMPRESSION - Compressible\n");
	printf("Input string:\n%s\nLength = %d\n", CompStr, inLen1);
	printf("Output string:\n%s\nLength = %d\n", outString1, strlen((char*)outString1));
	printf("Compression Ratio: %.2f\n", (float)(compressedLen1) / (float)(inLen1));

	// Incompressible String Results
	printf("\nTEST STRING COMPRESSION - Incompressible\n");
	printf("Input string:\n%s\nLength = %d\n", IncompStr, inLen2);
	printf("Output string:\n%s\nLength = %d\n", outString2, strlen((char*)outString2));
	printf("Compression Ratio: %.2f\n", (float)(compressedLen2) / (float)(inLen2));
	
	// Decompression String Results
	RLEdeCompress(outString1, strlen((char*)outString1), DecompStr, 140, cESC);
	printf("\nTEST STRING DECOMPRESSION\n");
	printf("\nOutput string:\n%s\n", DecompStr);


	// FILE COMPRESSION
	FILE* fptr1 = NULL;							// File pointer for input decompressed file
	FILE* fptr2 = NULL;							// File pointer for input compressed file
	char name1[] = ".\\Debug\\COMP.txt";		// Input decompressed file
	char name2[] = ".\\Debug\\DECOMP.txt";		// Input compressed file
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
		fileLen1++;								// Find length of file to compress
	}
	while (fgetc(fptr2) != EOF) {
		fileLen2++;								// Find length of file to decompress
	}
	fileOut1 = (char*)malloc(fileLen1);			// Allocate memory
	fileOut2 = (char*)malloc(fileLen2*10);		// Allocate memory

	fileOutLen1 = fileRLECompress(fptr1, fileLen1, fileOut1, cESC);	// Compress the file
	fclose(fptr1);

	printf("\nTEST FILE COMPRESSION\n");
	printf("Input file length: %d\n", fileLen1);
	printf("Output file:\n%s\nLength = %d\n", fileOut1, fileOutLen1);
	printf("\nCompression Ratio: %.4f\n", (float)fileOutLen1 / (float)fileLen1);

	fileRLEdeCompress(fptr2, fileLen2, fileOut2, cESC);
	printf("\nTEST FILE DECOMPRESSION\n");
	printf("\nOutput string:\n%s\n", fileOut2);
	fclose(fptr2);

	return(0);
}