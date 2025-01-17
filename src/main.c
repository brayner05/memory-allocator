#include <stdio.h>
#include <string.h>
#include "sys_brk.h"
#include "memalloc.h"

void print_free();

int main(void) {
    heap_alloc(10);
    void *ptr = heap_alloc(16);
    heap_alloc(30);
    heap_free(ptr);
    print_free();
    puts("");
    heap_alloc(16);
    print_free();
}