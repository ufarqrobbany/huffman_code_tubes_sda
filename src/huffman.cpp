#include "../include/huffman.h"

#include "../include/menu.h"
#include "../include/utils.h"

// ========================================================== HUFFMAN PROCESS
// Fungsi untuk membuat node
Node* createNode(char karakter, int frekuensi) {
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
void updateNode(Node** head, char karakter) {
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
        Node* newNode = createNode(karakter, 1);
        if (prev == NULL) {
            // Tambah node baru sebagai head jika list kosong
            *head = newNode;
        } else {
            // Tambah node baru di akhir list
            prev->next = newNode;
        }
    }
}

// Fungsi untuk menghitung frekuensi karakter dan menyimpannya dalam linked list
void calcCharFrequency(char* str, Node** head) {
    // hitung panjang text
    int panjang = strlen(str);

    // Menghitung frekuensi setiap karakter
    for (int i = 0; i < panjang; i++) {
        updateNode(head, str[i]);
    }
}

// Fungsi untuk mengurutkan linked list berdasarkan frekuensi secara menaik dan karakter
void sortLinkedList(Node** head) {
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
Node* createBinaryTree(Node* head) {
    while (head != NULL && head->next != NULL) {
        // traversal linked list
        Node* left = head;
        Node* right = head->next;

        Node* newNode = createNode('\0', left->frekuensi + right->frekuensi);
        newNode->left = left;
        newNode->right = right;

        head = right->next;
        newNode->next = head;
        head = newNode;

        sortLinkedList(&head);
    }
    return head;
}

// Fungsi untuk mendapatkan kode Huffman untuk setiap karakter
void setCode(Node* root, char* code, int depth) {
    if (root == NULL) return;

    if (root->left == NULL && root->right == NULL) {
        root->code = (char*)malloc((depth + 1) * sizeof(char));
        strncpy(root->code, code, depth);
        root->code[depth] = '\0';
        return;
    }

    code[depth] = '0';
    setCode(root->left, code, depth + 1);

    code[depth] = '1';
    setCode(root->right, code, depth + 1);
}

// Fungsi untuk mencari kode Huffman dari karakter tertentu
char* getCode(Node* root, char karakter) {
    if (root == NULL) return NULL;

    if (root->left == NULL && root->right == NULL) {
        if (root->karakter == karakter) {
            return root->code;
        } else {
            return NULL;
        }
    }

    char* code = getCode(root->left, karakter);
    if (code == NULL) {
        code = getCode(root->right, karakter);
    }
    return code;
}

// Fungsi untuk mengubah string menjadi kode Huffman dan mengembalikan hasilnya
char* convertToHuffmanCode(char* str, Node* huffmanTree) {
    // Alokasi buffer untuk hasil konversi
    int panjang = strlen(str);
    // Asumsi panjang maksimum kode Huffman per karakter adalah 16 bit
    char* hasil = (char*)malloc(panjang * 16 * sizeof(char));
    if (hasil == NULL) {
        printf("Alokasi memori gagal\n");
        return NULL;
    }
    hasil[0] = '\0';  // Inisialisasi string kosong

    for (int i = 0; i < panjang; i++) {
        const char* code = getCode(huffmanTree, str[i]);
        if (code != NULL) {
            strcat(hasil, code);
        } else {
            strcat(hasil, "?");
        }
    }

    return hasil;
}

// ========================================================= HUFFMAN DISPLAY
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
        printBinaryTree(root->left, depth + 1);
        printBinaryTree(root->right, depth + 1);
    }
}

// Fungsi untuk mencetak kode Huffman dari setiap karakter
void printCode(Node* root) {
    if (root == NULL) return;

    if (root->left == NULL && root->right == NULL) {
        printf("Karakter: '%c', Kode: %s\n", root->karakter, root->code);
    }

    printCode(root->left);
    printCode(root->right);
}

void visualizeTree(Node* root) {
    FILE* file = fopen("tree_visualizations/huffman_tree.dot", "w");
    fprintf(file, "digraph G {\n");
    generateDotFile(root, file);
    fprintf(file, "}\n");
    fclose(file);

    // Run 'dot -Tpng huffman_tree.dot -o huffman_tree.png' to generate the PNG image
    system("dot -Tpng tree_visualizations/huffman_tree.dot -o tree_visualizations/huffman_tree.png");
    printf("PNG image generated: tree_visualization/huffman_tree.png\n");
}

void generateDotFile(struct Node* root, FILE* file) {
    if (root == NULL) return;

    if (!(root->left) && !(root->right)) {
        fprintf(file, "    \"%p\" [label=\"%c (%d)\"];\n", (void*)root, root->karakter, root->frekuensi);
    } else {
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

// ========================================================= SAVE LOAD
void saveTree(Node* root, FILE* file) {
    if (root == NULL) {
        fputc('0', file);
        return;
    }
    fputc('1', file);
    fwrite(&root->karakter, sizeof(char), 1, file);
    saveTree(root->left, file);
    saveTree(root->right, file);
}

Node* loadTree(FILE* file) {
    char flag = fgetc(file);
    if (flag == '0') {
        return NULL;
    }
    Node* node = (Node*)malloc(sizeof(Node));
    fread(&node->karakter, sizeof(char), 1, file);
    node->left = loadTree(file);
    node->right = loadTree(file);
    node->next = NULL;
    node->code = NULL;
    return node;
}

// ========================================================= COMPRESS
void compressProcess(char* str) {
    Node* head = NULL;
    printTitle("Tahap 1 - Hitung Frekuensi Karakter", 60);
    printf("Buat Node untuk Setiap Karakter, Hitung Frekuensi, Susun Linked List\n");
    calcCharFrequency(str, &head);
    printFrequency(head);

    printTitle("Tahap 2 - Pembuatan Antrian Prioritas", 60);
    printf("Urutkan Linked List berdasarkan Frekuensi (Ascending)\n");
    sortLinkedList(&head);
    printFrequency(head);

    printTitle("Tahap 3 - Pembangunan Huffman Tree", 60);
    printf("Buat Binary Tree dari Linked List yang telah diurutkan, buat visualisasi tree\n");
    Node* huffmanTree = createBinaryTree(head);
    printBinaryTree(huffmanTree, 0);
    visualizeTree(huffmanTree);

    printTitle("Tahap 4 - Penetapan Kode Huffman untuk Setiap Karakter", 60);
    printf("Traversal Binary Tree, set kode huffman untuk setiap karakter pada Node\n");
    char code[100];
    setCode(huffmanTree, code, 0);
    printCode(huffmanTree);

    printTitle("Tahap 5 - Pengkodean Teks", 60);
    char* huffmanCode = convertToHuffmanCode(str, huffmanTree);
    printf("%s\n", huffmanCode);

    printTitle("Tahap 6 - Simpan Hasil Kompress", 60);
    printf("Simpan data hasil kompres beserta tree nya\n");
    printf("compressed_files/compressed_data.bin\n\n");
    compressData(str, huffmanTree, huffmanCode, "compressed_data.bin");

    printf("Tekan Enter untuk kembali...");
    getchar();

    // Bebaskan memori
    Node* current = head;
    while (current != NULL) {
        Node* next = current->next;
        free(current->code);
        free(current);
        current = next;
    }
}

void compressData(const char* input, Node* huffmanTree, const char* huffmanCode, const char* filename) {
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "compressed_files/%s", filename);

    FILE* file = fopen(filepath, "wb");

    if (file == NULL) {
        perror("Error opening file for writing");
        return;
    }

    // Save input length
    int length = strlen(input);
    fwrite(&length, sizeof(int), 1, file);

    // Save Huffman Tree
    saveTree(huffmanTree, file);

    // Save encoded data length
    int huffmanCodeLength = strlen(huffmanCode);
    fwrite(&huffmanCodeLength, sizeof(int), 1, file);

    // Save encoded data
    fwrite(huffmanCode, sizeof(char), huffmanCodeLength, file);

    fclose(file);
}

// ========================================================= DECOMPRESS
void decompressData(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file for reading");

        printf("\nTekan Enter untuk kembali...");
        getchar();
        return;
    }

    // Read input length
    int length;
    fread(&length, sizeof(int), 1, file);

    // Load Huffman Tree
    Node* huffmanTree = loadTree(file);

    // Read encoded data length
    int huffmanCodeLength;
    fread(&huffmanCodeLength, sizeof(int), 1, file);

    // Read encoded data
    char* huffmanCode = (char*)malloc(huffmanCodeLength + 1);
    fread(huffmanCode, sizeof(char), huffmanCodeLength, file);
    huffmanCode[huffmanCodeLength] = '\0';

    // Decode data
    char* decoded = (char*)malloc(length + 1);
    Node* current = huffmanTree;
    int index = 0;

    for (int i = 0; i < huffmanCodeLength; i++) {
        current = (huffmanCode[i] == '0') ? current->left : current->right;
        if (current->left == NULL && current->right == NULL) {
            decoded[index++] = current->karakter;
            current = huffmanTree;
        }
    }

    decoded[length] = '\0';
    printf("Decoded string: %s\n", decoded);

    printf("Tekan Enter untuk kembali...");
    getchar();

    free(decoded);
    free(huffmanCode);
    fclose(file);

    // Bebaskan memori tree
    freeTree(huffmanTree);
}

// ========================================================= FREE MEMORY
void freeTree(Node* root) {
    if (root == NULL) {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    free(root->code);
    free(root);
}