#ifndef ChunkyLib
#define ChunkyLib

#define ChunkyLibV 1.0

#include <stdio.h>
#include "./ChunkyLib.h"

int CreateCRC (char* data, int dataType) {}

int CreateChunk (char* data, int dataType) {}

int FileToChunk (char* fileIn, char* folderOut, unsigned long FInlenght, unsigned long MaxChunkLenght) {
	FILE *fileIn;
	char* chs;
	// if the file is found, return the content of the file
	if ((fileIn = fopen(fileIn, "r")) != NULL) {
		// get the lenght of the file
		fseek(fileIn, 0, SEEK_END);
		unsigned long res = ftell(fileIn);
		fseek(fileIn, 0, SEEK_SET);
		// if FInlenght is bigest than the opened file FInlenght is the size of the file
		// if FInlenght is 0 FInlenght is the size of the file
		FInlenght = (FInlenght > res || FInlenght == 0) ? res : FInlenght;
		for (int id = 1; id%MaxChunkLenght ;) {
			//
		}
		chs = (char*)calloc(sizeof(char), FInlenght);
		fread(chs, sizeof(char), FInlenght, fileIn);
		// close the file
		fclose(fileIn);
	} else return 1;
}

int ChunkTofile (char* folderIn, char* fileOut) {}

#endif