#include "huffman.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Fungsi untuk membuat node baru
Node* buatNode(char karakter, int frekuensi) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->karakter = karakter;
    node->frekuensi = frekuensi;
    node->code = NULL;
    node->code_length = 0;
    node->next = NULL;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Fungsi untuk menambah atau memperbarui node dalam linked list
void tambahAtauPerbaruiNode(Node** head, char karakter) {
    Node* current = *head;
    Node* prev = NULL;

    // Cari karakter dalam linked list
    while (current != NULL && current->karakter != karakter) {
        prev = current;
        current = current->next;
    }

    // Jika karakter ditemukan, perbarui frekuensinya
    if (current != NULL) {
        current->frekuensi++;
    } else {
        // Jika karakter tidak ditemukan, buat node baru
        Node* newNode = buatNode(karakter, 1);
        if (prev == NULL) {
            // Tambah node baru sebagai head jika list kosong
            *head = newNode;
        } else {
            // Tambah node baru di akhir list
            prev->next = newNode;
        }
    }
}

void cetakJudul(char* text, int max_length) {
    int text_length = strlen(text);

    printf("\n");
    printf("%c", 201);
    for (int i = 0; i < max_length; i++) {
        printf("%c", 205);
    }
    printf("%c\n", 187);
    printf("%c %s", 186, text);
    for (int i = 0; i < max_length - text_length - 2; i++) {
        printf(" ");
    }
    printf(" %c\n", 186);
    printf("%c", 200);
    for (int i = 0; i < max_length; i++) {
        printf("%c", 205);
    }
    printf("%c\n\n", 188);
}

// Fungsi untuk menghitung frekuensi karakter dan menyimpannya dalam linked list
void hitungFrekuensiKarakter(const char* str, Node** head) {
    int panjang = strlen(str);

    // Menghitung frekuensi setiap karakter
    for (int i = 0; i < panjang; i++) {
        tambahAtauPerbaruiNode(head, str[i]);
    }
}

// Fungsi untuk mencetak hasil frekuensi dalam format tabel
void cetakFrekuensi(const Node* head) {
    // 1
    printf("%c", 201);
    for (int i = 0; i < 11; i++)
        printf("%c", 205);
    const Node* current = head;
    while (current != NULL) {
        printf("%c", 203);
        for (int i = 0; i < 11; i++)
            printf("%c", 205);
        current = current->next;
    }
    printf("%c\n", 187);

    // 2
    printf("%c Karakter  ", 186);
    current = head;
    while (current != NULL) {
        printf("%c    '%c'    ", 186, current->karakter);
        current = current->next;
    }
    printf("%c\n", 186);

    // 3
    printf("%c", 204);
    for (int i = 0; i < 11; i++)
        printf("%c", 205);
    current = head;
    while (current != NULL) {
        printf("%c", 206);
        for (int i = 0; i < 11; i++)
            printf("%c", 205);
        current = current->next;
    }
    printf("%c\n", 185);

    // 4
    printf("%c Frekuensi ", 186);
    current = head;
    while (current != NULL) {
        char str[12];
        snprintf(str, 12, "%d", current->frekuensi);
        int length = strlen(str);

        int padding = (11 - length) / 2;
        printf("%c", 186);
        for (int j = 0; j < padding; j++)
            printf(" ");

        printf("%d", current->frekuensi);

        for (int j = 0; j < (11 - length - padding); j++)
            printf(" ");

        current = current->next;
    }
    printf("%c\n", 186);

    // 5
    printf("%c", 200);
    for (int i = 0; i < 11; i++)
        printf("%c", 205);
    current = head;
    while (current != NULL) {
        printf("%c", 202);
        for (int i = 0; i < 11; i++)
            printf("%c", 205);
        current = current->next;
    }
    printf("%c\n", 188);
}

// Fungsi untuk mengurutkan linked list berdasarkan frekuensi secara menaik dan karakter
void urutkanFrekuensi(Node** head) {
    if (*head == NULL) return;

    Node* sorted = NULL;

    Node* current = *head;
    // selama node bukan null
    while (current != NULL) {
        // ambil node selanjutnya
        Node* next = current->next;

        // jika sorted null || frekuensi sorted lebih besar dari frekuensi current || frekuensi dan karakter sama
        if (sorted == NULL || sorted->frekuensi > current->frekuensi || (sorted->frekuensi == current->frekuensi && sorted->karakter > current->karakter)) {
            current->next = sorted;
            sorted = current;
        } else {
            Node* temp = sorted;

            // jika temp next bukan null && (frekuensi temp next lebih kecil dari frekuensi current || frekuensi sama dan karakter temp next lebih kecil dari karakter current
            while (temp->next != NULL && (temp->next->frekuensi < current->frekuensi || (temp->next->frekuensi == current->frekuensi && temp->next->karakter < current->karakter))) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        current = next;
    }
    *head = sorted;
}

// Fungsi untuk membuat pohon Huffman
Node* buatHuffmanTree(Node* head) {
    while (head != NULL && head->next != NULL) {
        // traversal linked list
        Node* left = head;
        Node* right = head->next;

        Node* newNode = buatNode('\0', left->frekuensi + right->frekuensi);
        newNode->left = left;
        newNode->right = right;

        head = right->next;
        newNode->next = head;
        head = newNode;

        urutkanFrekuensi(&head);
    }
    return head;
}

// Fungsi untuk mencetak pohon Huffman (pre-order traversal)
void cetakHuffmanTree(Node* root, int depth) {
    if (root) {
        for (int i = 0; i < depth; i++) {
            printf("  ");
        }
        if (root->karakter != '\0') {
            printf("'%c': %d\n", root->karakter, root->frekuensi);
        } else {
            printf("Node: %d\n", root->frekuensi);
        }
        cetakHuffmanTree(root->left, depth + 1);
        cetakHuffmanTree(root->right, depth + 1);
    }
}

// Fungsi untuk mendapatkan kode Huffman untuk setiap karakter
void dapatkanKodeHuffman(Node* root, char* code, int depth) {
    if (root == NULL) return;

    if (root->left == NULL && root->right == NULL) {
        root->code = (char*)malloc((depth + 1) * sizeof(char));
        strncpy(root->code, code, depth);
        root->code[depth] = '\0';
        return;
    }

    code[depth] = '0';
    dapatkanKodeHuffman(root->left, code, depth + 1);

    code[depth] = '1';
    dapatkanKodeHuffman(root->right, code, depth + 1);
}

// Fungsi untuk mencetak kode Huffman dari setiap karakter
void cetakKodeHuffman(const Node* root) {
    if (root == NULL) return;

    if (root->left == NULL && root->right == NULL) {
        printf("Karakter: '%c', Kode: %s\n", root->karakter, root->code);
    }

    cetakKodeHuffman(root->left);
    cetakKodeHuffman(root->right);
}

// Fungsi untuk mencari kode Huffman dari karakter tertentu
const char* cariKodeHuffman(const Node* root, char karakter) {
    if (root == NULL) return NULL;

    if (root->left == NULL && root->right == NULL) {
        if (root->karakter == karakter) {
            return root->code;
        } else {
            return NULL;
        }
    }

    const char* code = cariKodeHuffman(root->left, karakter);
    if (code == NULL) {
        code = cariKodeHuffman(root->right, karakter);
    }
    return code;
}

// Fungsi untuk mengubah string menjadi kode Huffman
void ubahStringMenjadiHuffman(const char* str, const Node* huffmanTree) {
    int panjang = strlen(str);
    printf("String dalam kode Huffman: ");
    for (int i = 0; i < panjang; i++) {
        const char* code = cariKodeHuffman(huffmanTree, str[i]);
        if (code != NULL) {
            printf("%s", code);
        } else {
            printf("?");
        }
    }
    printf("\n");
}

// Fungsi untuk memeriksa apakah node adalah daun
int isLeaf(struct Node* head) {
    return !(head->left) && !(head->right);
}

// Fungsi untuk menghasilkan file DOT untuk visualisasi pohon Huffman
void generateDotFile(struct Node* root, FILE* file) {
    if (root == NULL) return;

    if (isLeaf(root)) {
        // Jika node adalah daun, cetak label node
        fprintf(file, "    \"%p\" [label=\"%c (%d)\"];\n", (void*)root, root->karakter, root->frekuensi);
    } else {
        // Jika node bukan daun, cetak label node
        fprintf(file, "    \"%p\" [label=\"%d\"];\n", (void*)root, root->frekuensi);

        if (root->left) {
            fprintf(file, "    \"%p\" -> \"%p\" [label=\"0\"];\n", (void*)root, (void*)root->left);
            generateDotFile(root->left, file);
        }

        if (root->right) {
            fprintf(file, "    \"%p\" -> \"%p\" [label=\"1\"];\n", (void*)root, (void*)root->right);
            generateDotFile(root->right, file);
        }
    }
}

// SAVE LOAD
// Fungsi untuk menyimpan node ke dalam file binary
void writeNode(FILE* file, Node* node) {
    if (node == NULL) return;

    fwrite(&node->karakter, sizeof(char), 1, file);
    fwrite(&node->frekuensi, sizeof(int), 1, file);
    fwrite(&node->code_length, sizeof(int), 1, file);

    // Tulis jika node punya anak
    uint8_t hasLeft = (node->left != NULL);
    uint8_t hasRight = (node->right != NULL);
    fwrite(&hasLeft, sizeof(uint8_t), 1, file);
    fwrite(&hasRight, sizeof(uint8_t), 1, file);

    if (hasLeft) writeNode(file, node->left);
    if (hasRight) writeNode(file, node->right);
}

// Simpan huffman tree dalam binary file
void saveHuffmanTree(Node* root, const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Error opening file for writing");
        return;
    }
    writeNode(file, root);
    fclose(file);
}

// Baca node dari binary file (Pre-Oder)
Node* readNode(FILE* file) {
    Node* node = (Node*)malloc(sizeof(Node));

    if (fread(&node->karakter, sizeof(char), 1, file) != 1) {
        free(node);
        return NULL;
    }
    fread(&node->frekuensi, sizeof(int), 1, file);
    fread(&node->code_length, sizeof(int), 1, file);

    uint8_t hasLeft, hasRight;
    fread(&hasLeft, sizeof(uint8_t), 1, file);
    fread(&hasRight, sizeof(uint8_t), 1, file);

    node->left = hasLeft ? readNode(file) : NULL;
    node->right = hasRight ? readNode(file) : NULL;

    node->code = NULL;
    node->next = NULL;

    return node;
}

// Load huffman tree dari binary file
Node* loadHuffmanTree(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file for reading");
        return NULL;
    }
    Node* root = readNode(file);
    fclose(file);
    return root;
}

// COMPRESS DECOMPRESS
// Fungsi untuk kompres data menggunakan huffman coding dan simpan dalam binary file
void compressData(const char* input, Node* huffmanTree, const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Error opening file for writing");
        return;
    }

    int length = strlen(input);
    fwrite(&length, sizeof(int), 1, file);

    for (int i = 0; i < length; i++) {
        const char* code = cariKodeHuffman(huffmanTree, input[i]);
        if (code != NULL) {
            uint8_t code_length = strlen(code);
            fwrite(&code_length, sizeof(uint8_t), 1, file);
            fwrite(code, sizeof(char), code_length, file);
        }
    }

    fclose(file);
}

// Decompress data
void decompressData(const char* filename, Node* huffmanTree, char* output) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file for reading");
        return;
    }

    int length;
    fread(&length, sizeof(int), 1, file);

    Node* current = huffmanTree;
    int output_index = 0;

    for (int i = 0; i < length; i++) {
        uint8_t code_length;
        fread(&code_length, sizeof(uint8_t), 1, file);

        for (int j = 0; j < code_length; j++) {
            char bit;
            fread(&bit, sizeof(char), 1, file);

            if (bit == '0') {
                current = current->left;
            } else {
                current = current->right;
            }

            if (isLeaf(current)) {
                output[output_index++] = current->karakter;
                current = huffmanTree;
            }
        }
    }
    output[output_index] = '\0';

    fclose(file);
}
