Node* createNode(char karakter, int frekuensi);
void updateNode(Node** head, char karakter);
void calcCharFrequency(const char* str, Node** head);
void sortLinkedList(Node** head);
Node* createBinaryTree(Node* head);
void setCode(Node* root, char* code, int depth);
const char* getCode(const Node* root, char karakter);
char* convertToHuffmanCode(const char* str, const Node* huffmanTree);