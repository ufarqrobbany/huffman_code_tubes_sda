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

// Fungsi untuk membuat node baru
Node* buatNode(char karakter, int frekuensi) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->karakter = karakter;
    node->frekuensi = frekuensi;
    node->code = NULL;
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
    while (current != NULL) {
        Node* next = current->next;
        if (sorted == NULL || sorted->frekuensi > current->frekuensi ||
            (sorted->frekuensi == current->frekuensi && sorted->karakter > current->karakter)) {
            current->next = sorted;
            sorted = current;
        } else {
            Node* temp = sorted;
            while (temp->next != NULL &&
                   (temp->next->frekuensi < current->frekuensi ||
                    (temp->next->frekuensi == current->frekuensi && temp->next->karakter < current->karakter))) {
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

// Fungsi utama
int main() {
    system("cls");  // Uncomment if running on Windows

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
