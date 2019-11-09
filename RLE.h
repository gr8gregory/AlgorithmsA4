/*
RLE.h: Interface of RLE compression / decompression functions

	Author: Gregory Huras
	Copyright 2019
*/


// Prototypes
int RLECompress(unsigned char* in, int iInLen, unsigned char* out, int iOutMax, unsigned char cESC);

int RLEdeCompress(unsigned char* in, int iInLen, unsigned char* out, int iOutMax, unsigned char cESC);

void fileRLECompress(FILE* fp, int fileLen, FILE* fout, unsigned char cESC);

#pragma once