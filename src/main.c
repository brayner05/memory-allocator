#include <stdio.h>
#include <string.h>
#include "sys_brk.h"
#include "memalloc.h"

void print_free();

enum Action {
    ALLOC = 'A', LIST = 'L', FREE = 'F'
};

int main(void) {
    while (1) {
        puts("Type A to allocate memory, or L to list allocated memory.");
        printf("> ");

        size_t to_alloc = 0;
        void *to_free = NULL;

        int action = getchar();
        switch (action) {
            case ALLOC: 
                printf("How much memory would you like to allocate?\n> ");
                scanf("%lu", &to_alloc);
                if (heap_alloc(to_alloc) != NULL) {
                    printf("Allocated %lu bytes of memory\n", to_alloc);
                }
                getchar();
                break;

            case LIST:
                print_free();
                getchar();
                break;

            case FREE:
                scanf("%p", &to_free);
                heap_free(to_free);
                getchar();
                break;

            default: puts("Invalid Option"); break;
        }
        puts("\n");
    }
}