#include "ram.h"

// инкапсуляция
static int ram_buffer[8] = {0};

void write(int index, int value) {
    if (index >= 0 && index < 8) {
        ram_buffer[index] = value;
    }
}

int read(int index) {
    if (index >= 0 && index < 8) {
        return ram_buffer[index];
    }
    return 0;
}
