#include "syscall.h"
void main() {
    int i;
    for(i = 9; i >= 5; i--) {
        Sleep(1000000);
        PrintInt(i);
    }
    return 0;
}
