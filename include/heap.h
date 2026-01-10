#ifndef HEAP_H
#define HEAP_H

#include <stddef.h>
#include <stdbool.h>

typedef struct Heap heap_t;

typedef int (*heap_cmp_fn)(const void *a, const void *b);
// < 0 => a has lower priority , > 0 => a has higher priority

heap_t* heap_init(size_t capacity, heap_cmp_fn cmp);
bool heap_is_empty(heap_t* heap);
bool is_size_one(heap_t* heap);
void* heap_top(heap_t* heap);
void heap_push(heap_t* heap, void* data);
void* heap_pop(heap_t* heap);
void heap_destroy(heap_t* heap);

#endif
