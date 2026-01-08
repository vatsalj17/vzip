#include "heap.h"

#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

typedef struct Heap {
	void** data;
	size_t size;
	size_t capacity;
	heap_cmp_fn cmp;
} heap_t;

heap_t* heap_init(size_t capacity, heap_cmp_fn cmp) {
    if (capacity == 0) return NULL;
	heap_t* new = malloc(sizeof(heap_t));
	if (!new) return NULL;
	new->cmp = cmp;
	new->capacity = capacity;
	new->size = 0;
	void** arr = calloc(capacity, sizeof(void*));
	if (!arr) {
		free(new);
		return NULL;
	}
	new->data = arr;
	return new;
}

void heap_push(heap_t* heap, void* data) {
	if (!heap) return;
	if (heap->size == heap->capacity) {
		size_t new_cap = heap->capacity * 2;
		void** arr = realloc(heap->data, new_cap * sizeof(void*));
		if (!arr) {
            fprintf(stderr, "realloc failed in heap_push\n");
            exit(1);
            // return;
        }
		heap->data = arr;
		heap->capacity = new_cap;
	}
	size_t index = heap->size++;
	heap->data[index] = data;
	while (index > 0) {
		size_t parent = (index - 1) / 2;
		if (heap->cmp(heap->data[index], heap->data[parent]) > 0) {
			swap(&heap->data[index], &heap->data[parent]);
			index = parent;
		} else {
			break;
		}
	}
}

void* heap_top(heap_t* heap) {
	if (!heap || heap_is_empty(heap)) return NULL;
	return heap->data[0];
}

void* heap_pop(heap_t* heap) {
	if (!heap || heap_is_empty(heap)) return NULL;
    void* result = heap->data[0];
	heap->data[0] = heap->data[--heap->size];
	size_t i = 0;
	while (i < heap->size) {
		size_t left = 2 * i + 1;
		size_t right = 2 * i + 2;
        size_t largest = i;
		if (left < heap->size && heap->cmp(heap->data[largest], heap->data[left]) < 0) {
			largest = left;
		} 
        if (right < heap->size && heap->cmp(heap->data[largest], heap->data[right]) < 0) {
			largest = right;
		} 
        if (largest != i) {
            swap(&heap->data[i], &heap->data[largest]);
            i = largest;
        } else {
            break;
        }
	}
    return result;
}

void heap_destroy(heap_t* heap) {
    if (!heap) return;
    free(heap->data);
    free(heap);
}

bool heap_is_empty(heap_t* heap) {
    return heap->size == 0;
}

bool is_size_one(heap_t* heap) {
    return heap->size == 1;
}
