#include <stdio.h>
#include <string.h>
#include "sys_brk.h"
#include "memalloc.h"

int main(void) {
    char *message = heap_alloc(16 * sizeof(char));
    strcpy(message, "Hello, World?");
    puts(message);
}