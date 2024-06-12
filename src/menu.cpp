#include "../include/menu.h"

#include "../include/huffman.h"
#include "../include/utils.h"

void printTitle(char* text, int max_length) {
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

void printMainMenu() {
    system("cls");
    printTitle("HUFFMAN CODE", 60);
    printf("1. Kompres\n");
    printf("2. Dekompres\n");
    printf("3. Keluar\n\n");
    printf("Pilih: ");
}

void printCompressMenu() {
    system("cls");
    printTitle("HUFFMAN CODE - COMPRESS", 60);
    printf("1. Pilih File\n");
    printf("2. Input Text\n");
    printf("3. Kembali\n\n");
    printf("Pilih: ");
}

void compressMenu() {
    int key;

    do {
        printCompressMenu();
        scanf("%d", &key);
        clearBuffer();

        switch (key) {
            case 1:
                compressOpenFile();
                break;
            case 2:
                compressInputText();
            default:
                break;
        }
    } while (key != 3);
}

void compressInputText() {
    char str[100];

    printf("Masukkan sebuah string: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = 0;

    compressProcess(str);
}

void compressOpenFile() {
    // decompressData("compressed_data.bin");
    // printf("Tekan Enter untuk kembali...");
    // getchar();
    return;
}

void decompressMenu() {
    char filename[256];
    printf("Enter the path to the compressed file: ");
    scanf("%255s", filename);
    clearBuffer();

    decompressData(filename);
}