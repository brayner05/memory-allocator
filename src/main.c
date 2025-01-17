#include <stdio.h>
#include <string.h>
#include "sys_brk.h"

int main(void) {
    char *ptr = (char *) _sbrk(16);
    strcpy(ptr, "Hello, World!\n");
    puts(ptr);
}