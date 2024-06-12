#include <stdint.h>
#include <stdio.h>

#include "../include/huffman.h"

void decompress();
void decompressFile(const char* filename, Node* huffmanTree, char* output);