/*
main2.cpp: Client for Huff.cpp compression / decompression functions

	Author: Gregory Huras, Caleb Hoeksema, Laura Muhlbauerova
	Copyright 2019
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Huff.h"
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
	
	Menu();

	return(0);
}

