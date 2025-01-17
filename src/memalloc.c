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

/**
 * Align a quantity of memory to the machines register size.
 */
static inline size_t align_up(size_t size, size_t align) {
    return (size + align - 1) & ~(align - 1);
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
        if (chunk->is_free && chunk->size >= total_size) {
            break;
        }
        chunk = chunk->next;
    }

    if (chunk == NULL) {
        chunk = (MemoryChunk *) _sbrk(total_size);
        if (chunk == (void *) -1) {
            return NULL;
        }

        *chunk = (MemoryChunk) {
            .address = chunk,
            .is_free = 0,
            .next = NULL,
            .size = size
        };

        return chunk + 1;
    }

    return chunk + 1;
}

int heap_free(void *ptr) {
    MemoryChunk *chunk = free_list;
    while (chunk != NULL) {
        if (chunk->address == ptr) {
            chunk->is_free = 1;
            return 0;
        }
    }
    return -1;
}