#ifndef SYS_BRK_H
#define SYS_BRK_H

#include <stddef.h>

/**
 * Set the program break
 * @param ptr The address to set the program break to. If ptr is set to 0,
 * this function will return the current program break.
 * @return 0 on success, -1 on error, or the current program break if ptr is 0
 */
extern int _brk(void *ptr);

/**
 * Increase the program break by a given offset.
 * @param offset The number of bytes by which to offset the program break.
 * @return The previous program break on success, `(void *) -1` on error.
 */
extern void *_sbrk(ptrdiff_t offset);

#endif