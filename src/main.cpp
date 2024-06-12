#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/menu.h"
#include "../include/utils.h"

int main() {
    int key;

    do {
        printMainMenu();
        scanf("%d", &key);
        clearBuffer();

        switch (key) {
            case 1:
                compressMenu();
                break;
            case 2:
                decompressMenu();
            default:
                break;
        }
    } while (key != 3);

    return 0;
}
