#include "../include/huffman_display.h"

// Fungsi untuk mencetak hasil frekuensi dalam format tabel
void printFrequency(const Node* head) {
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

// Fungsi untuk mencetak pohon Huffman (pre-order traversal)
void printBinaryTree(Node* root, int depth) {
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

// Fungsi untuk mencetak kode Huffman dari setiap karakter
void printCode(const Node* root) {
    if (root == NULL) return;

    if (root->left == NULL && root->right == NULL) {
        printf("Karakter: '%c', Kode: %s\n", root->karakter, root->code);
    }

    cetakKodeHuffman(root->left);
    cetakKodeHuffman(root->right);
}
