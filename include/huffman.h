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
    int code_length;
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

// HUFFMAN DISPLAY
void printFrequency(const Node* head);
void printBinaryTree(Node* root, int depth);
void visualizeTree(Node* root);
void generateDotFile(struct Node* root, FILE* file);
void printCode(Node* root);

// SAVE LOAD
void saveTree(Node* root, FILE* file);
Node* loadTree(FILE* file);

// COMPRESS DECOMPRESS
void compressProcess(char* str);
void compressData(const char* input, Node* huffmanTree, const char* huffmanCode, const char* filename);
void decompressData(const char* filename);

// FREE MEMORY
void freeTree(Node* root);
// void decompress();
// void decompressFile(const char* filename, Node* huffmanTree, char* output);

// // save load
// void writeNode(FILE* file, Node* node);
// void saveHuffmanTree(Node* root, const char* filename);
// Node* readNode(FILE* file);
// Node* loadHuffmanTree(const char* filename);
