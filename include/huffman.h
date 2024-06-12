#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_WIDTH 13

// STRUKTUR DATA
typedef struct Node {
    char karakter;
    int frekuensi;
    char* code;
    struct Node* next;
    struct Node* left;
    struct Node* right;
} Node;

// HUFFMAN PROCESS
Node* createNode(char karakter, int frekuensi);
void updateNode(Node** head, char karakter);
void calcCharFrequency(char* str, Node** head);
void sortLinkedList(Node** head);
Node* createBinaryTree(Node* head);
void setCode(Node* root, char* code, int depth);
char* getCode(Node* root, char karakter);
char* convertToHuffmanCode(char* str, Node* huffmanTree);
char* decodeHuffmanCode(Node* root, char* huffmanCode, int length);

// HUFFMAN DISPLAY
void printFrequency(Node* head);
void printBinaryTree(Node* root, int depth);
void visualizeTree(Node* root, char* filename);
void generateDotFile(struct Node* root, FILE* file);
void printCode(Node* root);

// SAVE LOAD
void saveTree(Node* root, FILE* file);
Node* loadTree(FILE* file);

// COMPRESS DECOMPRESS
void compressProcess(char* str, char* outputFilename, char* originalExtension);
void compressData(char* input, Node* huffmanTree, char* huffmanCode, char* filename, char* originalExtension);
void decompressData(char* filename);

// FREE MEMORY
void freeTree(Node* root);