#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "huffman.h"

void kompres() {
    system("cls");
    char str[100];
    Node* head = NULL;

    printf("Masukkan sebuah string: ");
    fgets(str, sizeof(str), stdin);

    // Menghilangkan karakter newline jika ada
    str[strcspn(str, "\n")] = 0;

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
    printf("Run 'dot -Tpng huffman_tree.dot -o huffman_tree.png' to generate the PNG image.\n");

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

void dekompres() {
    system("cls");

    // Baca Huffman Tree dari file
    Node* loadedTree = loadHuffmanTree("huffman_tree.bin");

    // Dekompres
    char decompressed[256];
    decompressData("compressed_data.bin", loadedTree, decompressed);

    // Print hasil dekompres
    printf("Decompressed text: %s\n", decompressed);

    printf("\nTekan Enter untuk kembali...");
    getchar();
}

// Fungsi untuk membersihkan buffer input
void bersihkanBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Fungsi utama
int main() {
    int key;

    do {
        system("cls");
        cetakJudul("HUFFMAN CODE", 60);
        printf("1. Kompres\n");
        printf("2. Dekompres\n");
        printf("3. Keluar\n\n");
        printf("Pilih: ");
        scanf("%d", &key);
        bersihkanBuffer();

        switch (key) {
            case 1:
                kompres();
                break;
            case 2:
                dekompres();
            default:
                break;
        }
    } while (key != 3);

    return 0;
}
