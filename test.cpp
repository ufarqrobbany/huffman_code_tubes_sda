#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_WIDTH 13

// Struktur untuk menyimpan karakter dan frekuensinya dalam linked list dan binary tree
typedef struct Node {
    char karakter;
    int frekuensi;
    struct Node* next;
    struct Node* left;
    struct Node* right;
} Node;

// Fungsi untuk membuat node baru
Node* buatNode(char karakter) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->karakter = karakter;
    node->frekuensi = 1;
    node->next = NULL;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Fungsi untuk membuat node baru dengan frekuensi tertentu
Node* buatNodeDenganFrekuensi(char karakter, int frekuensi) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->karakter = karakter;
    node->frekuensi = frekuensi;
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
        Node* newNode = buatNode(karakter);
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

// Fungsi untuk mengurutkan linked list berdasarkan frekuensi secara menaik
void urutkanFrekuensi(Node** head) {
    if (*head == NULL) return;

    Node* sorted = NULL;

    Node* current = *head;
    while (current != NULL) {
        Node* next = current->next;
        if (sorted == NULL || sorted->frekuensi >= current->frekuensi) {
            current->next = sorted;
            sorted = current;
        } else {
            Node* temp = sorted;
            while (temp->next != NULL && temp->next->frekuensi < current->frekuensi) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        current = next;
    }
    *head = sorted;
}

// Fungsi untuk menggabungkan dua node menjadi node baru
Node* gabungNode(Node* node1, Node* node2) {
    Node* newNode = buatNodeDenganFrekuensi('\0', node1->frekuensi + node2->frekuensi);
    newNode->left = node1;
    newNode->right = node2;
    return newNode;
}

// Fungsi untuk membuat pohon Huffman dari linked list
Node* buatHuffmanTree(Node* head) {
    while (head && head->next) {
        Node* node1 = head;
        Node* node2 = head->next;
        head = node2->next;
        Node* newNode = gabungNode(node1, node2);

        // Tambahkan newNode ke dalam linked list yang terurut berdasarkan frekuensi
        if (!head || newNode->frekuensi <= head->frekuensi) {
            newNode->next = head;
            head = newNode;
        } else {
            Node* current = head;
            while (current->next && current->next->frekuensi < newNode->frekuensi) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
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

    cetakJudul("Tahap 1", 60);

    // Menghitung frekuensi karakter
    hitungFrekuensiKarakter(str, &head);

    printf("Hitung Frekuensi\n");
    cetakFrekuensi(head);
    printf("\n");

    // Mengurutkan frekuensi secara menaik
    urutkanFrekuensi(&head);

    printf("Urutkan Berdasarkan Frekuensi (Ascending)\n");
    cetakFrekuensi(head);
    printf("\n");

    // Buat Huffman Tree dari linked list yang terurut
    Node* huffmanTree = buatHuffmanTree(head);

    printf("Pohon Huffman\n");
    cetakHuffmanTree(huffmanTree, 0);

    // Buka file untuk menulis output DOT
    FILE* file = fopen("huffman_tree.dot", "w");
    fprintf(file, "digraph G {\n");

    // Menulis edge dari pohon Huffman
    generateDotFile(huffmanTree, file);

    fprintf(file, "}\n");
    fclose(file);

    printf("DOT file generated: huffman_tree.dot\n");
    printf("Run 'dot -Tpng huffman_tree.dot -o huffman_tree.png' to generate the PNG image.\n");

    // Free memory
    // Node* current = huffmanTree;
    // while (current != NULL) {
    //     Node* next = current->next;
    //     free(current);
    //     current = next;
    // }

    return 0;
}