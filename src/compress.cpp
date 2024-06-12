#include "../include/compress.h"

#include "../include/huffman.h"
#include "../include/huffman_process.h"
#include "../include/menu.h"
#include "../include/utils.h"

void compressInputText() {
    char str[100];
    Node* head = NULL;

    printf("Masukkan sebuah string: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = 0;

    compressProcess(str, &head);

    // Bebaskan memori
    Node* current = head;
    while (current != NULL) {
        Node* next = current->next;
        free(current->code);
        free(current);
        current = next;
    }
}

void compressOpenFile() {
    return 0;
}

void compressProcess(char* str, Node** head) {
    printTitle("Tahap 1 - Hitung Frekuensi Karakter", 60);
    printf("Buat Node untuk Setiap Karakter, Hitung Frekuensi, Susun Linked List\n");
    calcCharFrequency(str, &head);
    printFrequency(head);

    printTitle("Tahap 2 - Pembuatan Antrian Prioritas", 60);
    printf("Urutkan Linked List berdasarkan Frekuensi (Ascending)\n");
    sortFrequency(&head);
    printFrequency(head);

    printTitle("Tahap 3 - Pembangunan Huffman Tree", 60);
    printf("Buat Binary Tree dari Linked List yang telah diurutkan, buat visualisasi tree\n");
    Node* huffmanTree = createBinaryTree(head);
    printBinaryTree(huffmanTree, 0);
    visualizeTree(huffmanTree);

    printTitle("Tahap 4 - Penetapan Kode Huffman untuk Setiap Karakter", 60);
    printf("Traversal Binary Tree, set kode huffman untuk setiap karakter pada Node\n");
    setCode(huffmanTree, char code[100], 0);
    printCode(huffmanTree);

    printTitle("Tahap 5 - Pengkodean Teks", 60);
    char* huffmanCode = convertToHuffmanCode(str, huffmanTree);
    printf("%s\n", huffmanCode);

    printTitle("Tahap 6 - Simpan Hasil Kompress", 60);
    prinf("Simpan text hasil kompres beserta tree nya\n");
    compressData(str, huffmanTree, "compressed_data.bin");

    printf("Tekan Enter untuk kembali...");
    getchar();
}

void compress() {
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