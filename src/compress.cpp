#include "../include/compress.h"

#include "../include/huffman.h"
#include "../include/menu.h"
#include "../include/utils.h"

void compressInputText() {
    char str[100];
    Node* head = NULL;

    printf("Masukkan sebuah string: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = 0;
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

    printf("\n");
    cetakJudul("Tahap 1 - Pengumpulan Frekuensi Karakter", 60);

    // Menghitung frekuensi karakter
    hitungFrekuensiKarakter(str, &head);

    printf("Hitung Frekuensi\n");
    cetakFrekuensi(head);
    printf("\n");

    cetakJudul("Tahap 2 - Pembuatan Antrian Prioritas", 60);

    // Mengurutkan frekuensi secara menaik
    urutkanFrekuensi(&head);

    printf("Urutkan Berdasarkan Frekuensi (Ascending)\n");
    cetakFrekuensi(head);
    printf("\n");

    cetakJudul("Tahap 3 - Pembangunan Huffman Tree", 60);

    // Membuat pohon Huffman
    Node* huffmanTree = buatHuffmanTree(head);

    printf("Pohon Huffman\n");
    cetakHuffmanTree(huffmanTree, 0);
    printf("\n");

    // Buka file untuk menulis output DOT
    FILE* file = fopen("huffman_tree.dot", "w");
    fprintf(file, "digraph G {\n");

    // Menulis edge dari pohon Huffman
    generateDotFile(huffmanTree, file);

    fprintf(file, "}\n");
    fclose(file);

    printf("DOT file generated: huffman_tree.dot\n");
    // Run 'dot -Tpng huffman_tree.dot -o huffman_tree.png' to generate the PNG image
    system("dot -Tpng huffman_tree.dot -o huffman_tree.png");

    cetakJudul("Tahap 4 - Penetapan Kode Huffman", 60);

    // Mendapatkan kode Huffman untuk setiap karakter
    char code[100];
    dapatkanKodeHuffman(huffmanTree, code, 0);

    printf("Kode Huffman\n");
    cetakKodeHuffman(huffmanTree);
    printf("\n");

    cetakJudul("Tahap 5 - Pengkodean Teks", 60);

    // Mengubah string menjadi kode Huffman
    ubahStringMenjadiHuffman(str, huffmanTree);
    printf("\n");

    // Simpan huffman tree
    cetakJudul("Tahap 6 - Simpan Huffman Tree ke dalam file Binary", 60);
    saveHuffmanTree(huffmanTree, "huffman_tree.bin");
    printf("huffman_tree.bin\n\n");

    // Simpan hasil kompres
    cetakJudul("Tahap 7 - Simpan Hasil Kompres", 60);
    compressData(str, huffmanTree, "compressed_data.bin");
    printf("compressed_data.bin\n\n");

    // Bebaskan memori
    Node* current = head;
    while (current != NULL) {
        Node* next = current->next;
        free(current->code);
        free(current);
        current = next;
    }

    printf("Tekan Enter untuk kembali...");
    getchar();
}