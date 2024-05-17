#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_WIDTH 13

// Struktur data
typedef struct Node {
    char karakter;
    int frekuensi;
    char* code;
    struct Node* next;
    struct Node* left;
    struct Node* right;
} Node;

// modul
Node* buatNode(char karakter, int frekuensi);
void hitungFrekuensiKarakter(const char* str, Node** head);
void tambahAtauPerbaruiNode(Node** head, char karakter);
void urutkanFrekuensi(Node** head);
Node* buatHuffmanTree(Node* head);
void dapatkanKodeHuffman(Node* root, char* code, int depth);
const char* cariKodeHuffman(const Node* root, char karakter);
void ubahStringMenjadiHuffman(const char* str, const Node* huffmanTree);

// modul menu (tampilan)
void cetakJudul(char* text, int max_length);
void cetakFrekuensi(const Node* head);
void cetakHuffmanTree(Node* root, int depth);
void cetakKodeHuffman(const Node* root);

// modul gambar tree
int isLeaf(struct Node* head);
void generateDotFile(struct Node* root, FILE* file);
