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
#include "huffman.h"


void Menu(void) {

	int error = 0;
	char userIn[2];
	char c;
	while (error == 0) {
		
		printf("Main Menu\n**********************************************************\n");

		printf("Huffman Compress File:(1) Huffman file Decompress:(2) Huffman Audio Compress:(3) Huffman Audio Decompress:(4)\n");
		scanf_s("%c", userIn, 2);

		error = 0;

		switch (userIn[0]) {
		case ('1'):
			while ((c = getchar()) != '\n' && (c != EOF)) {}				//flushes input 
			compress();
			break;
		case('2'):
			while ((c = getchar()) != '\n' && (c != EOF)) {}
			decompress();
			break;
		case ('3'):
			while ((c = getchar()) != '\n' && (c != EOF)) {}				//flushes input 
			audioCompress();
			break;
		case('4'):
			while ((c = getchar()) != '\n' && (c != EOF)) {}
			audioDecompress();
			break;
		default:
			printf("Invalid input\n\n");
			error = 1;
			while ((c = getchar()) != '\n' && (c != EOF)) {}
			break;
		}
		while ((c = getchar()) != '\n' && (c != EOF)) {};

	}
}

int main(void) {
	
	//Buffer Compression
	/*unsigned char myString[] = "AAAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBBBBCCCCCCCCCCCDDD";
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

	//RLEdeCompress(outString, strlen((char*)outString), SecondOutString, 140, cESC);
	//printf("\nOutput string %s\n", SecondOutString);




	/*************************************** Huffman*************************************************/
	
	Menu();

	return(0);
}

