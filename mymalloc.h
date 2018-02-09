#ifndef MYMALLOC_H
#define MYMALLOC_H

typedef struct _block{
    int size;
    char assigned;
    struct _block* next;
    struct _block* prev;
    void* address;
} block;

void initializeMainMemory();

void* mymalloc(size_t, char*, int);

void myfree(void*, char*, int);

#endif
