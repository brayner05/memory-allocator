# Memory Allocator (To be named)

## Allocating memory
Memory can be allocated from the heap, and subsequently freed using the `heap_alloc(1)` and `heap_free(1)` functions defined in `memalloc.h`. See an example below:

```c
char *message = heap_alloc(15 * sizeof(char));
if (message != NULL) {
    strcpy(message, "Hello, World!");
    puts(message);
    heap_free(message);
}
```

## Documentation
### `heap_alloc(1)`
#### Description
The `heap_alloc(1)` function allocates memory on the heap and then returns a pointer to that memory.

#### `size_t size`
The `heap_alloc(1)` function takes a `size_t` called `size` which represents how many bytes of memory to allocate.

### `heap_free(1)`
#### Description
The `heap_free(1)` function marks a chunk of memory allocated by `heap_alloc(1)` as free so that it can be used elsewhere in the program.

#### `void *ptr`
The `heap_free(1)` function takes a pointer to the memory to be freed.