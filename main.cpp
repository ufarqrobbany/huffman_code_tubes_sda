#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "huffman.h"

// Fungsi utama
int main() {
    system("cls");

    char str[100];
    Node* head = NULL;

    printf("Masukkan sebuah string: ");
    fgets(str, sizeof(str), stdin);

    // Menghilangkan karakter newline jika ada
    str[strcspn(str, "\n")] = 0;

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

    // Free memory
    Node* current = head;
    while (current != NULL) {
        Node* next = current->next;
        free(current->code);  // Free the Huffman code memory
        free(current);
        current = next;
    }

    return 0;
}
