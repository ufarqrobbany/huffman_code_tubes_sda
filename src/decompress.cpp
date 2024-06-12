#include "../include/decompress.h"

void decompress() {
    system("cls");

    Node* loadedTree = loadHuffmanTree("huffman_tree.bin");

    char decompressed[256];
    decompressFile("compressed_data.bin", loadedTree, decompressed);

    printf("Decompressed text: %s\n", decompressed);

    printf("\nTekan Enter untuk kembali...");
    getchar();
}

void decompressFile(const char* filename, Node* huffmanTree, char* output) {
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

            // is leaf
            if (!(current->left) && !(current->right)) {
                output[output_index++] = current->karakter;
                current = huffmanTree;
            }
        }
    }
    output[output_index] = '\0';

    fclose(file);
}