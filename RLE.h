/*
RLE.h: Interface of RLE compression / decompression functions

	Author: Gregory Huras, Caleb Hoeksema, Laura Muhlbauerova
	Copyright 2019
*/


//Function Prototypes

// String Processing Prototypes
int RLECompress(unsigned char* in, int iInLen, unsigned char* out, int iOutMax, unsigned char cESC);
int RLEdeCompress(unsigned char* in, int iInLen, unsigned char* out, int iOutMax, unsigned char cESC);

// File Processing Prototypes
int fileRLECompress(FILE* fp, int fileLen, char* fileout, unsigned char cESC);
int fileRLEdeCompress(FILE* fp, int fileLen, char* fileout, unsigned char cESC);

#pragma once