#include "../include/visualization.h"

void visualizeTree(Node* root) {
    FILE* file = fopen("huffman_tree.dot", "w");
    fprintf(file, "digraph G {\n");
    generateDotFile(root, file);
    fprintf(file, "}\n");
    fclose(file);

    // Run 'dot -Tpng huffman_tree.dot -o huffman_tree.png' to generate the PNG image
    system("dot -Tpng huffman_tree.dot -o huffman_tree.png");
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