/*
fileRLE.cpp: Implimentation of RLE compression / decompression functions for files

	Author: Gregory Huras
	Copyright 2019
*/
#pragma warning (disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Huff.h"
#include "huffman.h"
#include "sound.h"

unsigned char HuffmanCompression[29 + 384];
unsigned char HuffmanDecompression[1000];
unsigned char HuffmanInput[29];
int totalBytes = 0;
extern short iBigBuf[];												// buffer
extern long  lBigBufSize;											// total number of samples
short* iBigBufNew = (short*)malloc(lBigBufSize * sizeof(short));		// buffer used for reading recorded sound from file												// used to flush extra input

void compress(void) {


	printf("\nEnter a file to compress: ");
	scanf("%s", userIn);

	if (err = fopen_s(&fp, "Huffman.txt", "r") == 1) {
		printf("\nFailed to open the file\n");
		fclose(fp);
	}
	while ((c = fgetc(fp)) != EOF) {

		HuffmanInput[fileLen] = c;
		fileLen++;							//counts the length of the file
	}
	HuffmanInput[28] = '\0';
	totalBytes = Huffman_Compress(HuffmanInput, HuffmanCompression, 29);


	printf("\nInput string: %s\n", HuffmanInput);
	printf("\nCompression: %s\n", HuffmanCompression);
	printf("\nInput string length: %d\n", strlen((char*)HuffmanInput));
	printf("\nCompressed string Length: %d\n", totalBytes);
	printf("\nCompression Ratio: %.2f\n", (float)(totalBytes) / (float)strlen((char*)HuffmanInput));


	
	Menu();
	
}
void decompress(void) {
	
	Huffman_Uncompress(HuffmanCompression, HuffmanDecompression, totalBytes, 1000);
	printf("\nHuffmanDecompression: %s\n", HuffmanDecompression);

	if (err = fopen_s(&fp, "HuffmanDecompress.txt", "w") == 1) {
		printf("\nFailed to open the file\n");
		fclose(fp);
	}
	while (true) {
		c = HuffmanDecompression[counter];
		if (c == '\0') {
			break;
		}
		fputc(c, fp);
		counter++;
	}
	fclose(fp);
	Menu();

}
int audio(void) {

	InitializePlayback();
	InitializeRecording();

	// start recording
	RecordBuffer(iBigBuf, lBigBufSize);
	CloseRecording();

	fopen_s(&fp, "CompAudio.dat", "w");
	if (!fp) {
		printf("unable to open file.\n");
	}
	fwrite(iBigBuf, sizeof(short), lBigBufSize, fp);

	fseek(fp, 0L, 0);
	fseek(fp, 0L, SEEK_END);
	int sz = ftell(fp);
	fclose(fp);

	return(sz);
}
void audioCompress(void) {
	int size = audio();
	char s;

	unsigned char* buffer = (unsigned char *)malloc(size * sizeof(char));
	unsigned char* Comp = (unsigned char*)malloc(size * sizeof(char) + 384);
	unsigned char* decomp = (unsigned char*)malloc(size * sizeof(char));

	fp = fopen("CompAudio.dat", "r");
	counter = 0;
	while (!feof(fp)) {
		fread(&s, 1, 1, fp);
		
		buffer[counter] = s;
		counter++;
	}
	fclose(fp);

	totalBytes = Huffman_Compress(buffer, Comp, size);
	if (err = fopen_s(&fp, "AudioCompress.dat", "w") == 1) {
		printf("\nFailed to open the file\n");
		fclose(fp);
	}
	for (int i = 0; i < size; i++)
	{
		c = Comp[i];

		fputc(c, fp);
	}
	fclose(fp);

	
	
	Huffman_Uncompress(Comp, decomp, totalBytes, size);


	if (err = fopen_s(&fp, "AudioDecompress.dat", "w") == 1) {
		printf("\nFailed to open the file\n");
		fclose(fp);
	}
	for (int i = 0; i < totalBytes; i++)
	{
		c = decomp[i];

		fputc(c, fp);
	}
	fclose(fp);
	printf("\nInput string: %c\n", buffer);
	printf("\nCompressed string %c\n", Comp);
	printf("\nDecompressed string %c\n", decomp);
	printf("\nInput string Length: %d\n", size);
	printf("\nCompressed string Length: %d\n", totalBytes);
	printf("\nDeCompressed string Length: %d\n", size);
	printf("\nCompression Ratio: %.2f\n", (float)(totalBytes) / size);

	free(buffer);
	free(Comp);
	free(decomp);
}
void audioDecompress(void) {


} 
