#include "../include/utils.h"

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}