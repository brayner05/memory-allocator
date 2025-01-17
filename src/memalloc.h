#ifndef MEMALLOC_H
#define MEMALLOC_H
#include <stddef.h>

/**
 * Allocate memory from the heap.
 * @param size The number of bytes to allocate
 * @return A chunk of memory with 'size' bytes or NULL on error.
 */
void *heap_alloc(size_t size);

/**
 * Free memory allocated from the heap.
 * @param ptr A pointer to the memory to free
 * @return 0 on success, -1 on error
 */
int heap_free(void *ptr);

#endif