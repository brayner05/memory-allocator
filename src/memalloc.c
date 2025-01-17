#include "memalloc.h"
#include "sys_brk.h"

typedef struct MemoryChunk {
    size_t size;
    _Bool is_free;
    void *address;
    struct MemoryChunk *next;
} MemoryChunk;

// A linked-list representing all allocated memory.
static MemoryChunk *free_list = NULL;

// =====================================
// ! TO BE REMOVED
// =====================================

#define DEBUG
#ifdef DEBUG
#include <stdio.h>

void print_free(void) {
    MemoryChunk *chunk = free_list;
    while (chunk != NULL) {
        printf("[%p | %lub | %s] -> ", chunk->address, chunk->size, chunk->is_free ? "free" : "in use");
        chunk = chunk->next;
    }
}

#endif

/**
 * Align a quantity of memory to the machines register size.
 */
static inline size_t align_up(size_t size, size_t align) {
    return (size + align - 1) & ~(align - 1);
}

/**
 * 
 */
static void add_to_free_list(MemoryChunk *chunk) {
    if (free_list == NULL) {
        free_list = chunk;
        return;
    }

    chunk->next = free_list;
    free_list = chunk;
}


/**
 * Allocate memory on the heap.
 * @param size The number of bytes to allocate.
 * @return A pointer to memory on the heap on success, `NULL` on failure.
 */
void *heap_alloc(size_t size) {
    size_t total_size = size + sizeof(MemoryChunk);
    total_size = align_up(total_size, sizeof(void *));
    
    MemoryChunk *chunk = free_list;
    while (chunk != NULL) {
        if (chunk->is_free && chunk->size >= size) {
            break;
        }
        chunk = chunk->next;
    }

    if (chunk == NULL) {
        chunk = (MemoryChunk *) _sbrk(total_size);
        if (chunk == (void *) -1) {
            return NULL;
        }

        void *allocated_memory = (void *) chunk + sizeof(chunk);
        *chunk = (MemoryChunk) {
            .address = allocated_memory,
            .is_free = (_Bool) 0,
            .next = NULL,
            .size = size
        };

        add_to_free_list(chunk);
        return allocated_memory;
    }

    chunk->is_free = (_Bool) 0;
    return chunk->address;
}

int heap_free(void *ptr) {
    MemoryChunk *chunk = free_list;
    while (chunk != NULL) {
        if (chunk->address == ptr) {
            chunk->is_free = 1;
            return 0;
        }
        chunk = chunk->next;
    }
    return -1;
}
