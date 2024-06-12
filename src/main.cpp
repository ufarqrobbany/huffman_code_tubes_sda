#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "compress.h"
#include "decompress.h"
#include "huffman.h"
#include "menu.h"
#include "utils.h"
#include "visualization.h"

int main() {
    int key;

    do {
        printMainMenu();
        scanf("%d", &key);
        clearBuffer();

        switch (key) {
            case 1:
                compress();
                break;
            case 2:
                decompress();
            default:
                break;
        }
    } while (key != 3);

    return 0;
}
