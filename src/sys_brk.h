#ifndef SYS_BRK_H
#define SYS_BRK_H

extern void *_brk(void *ptr);
extern void *_sbrk(size_t offset);

#endif