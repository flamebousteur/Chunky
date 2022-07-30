#include <stdio.h>
#include "./ChunkyLib.h"

int main (int argc, char *args[]) {
	return FileToChunk("./test/data.txt", "./test/out/", 0)
}