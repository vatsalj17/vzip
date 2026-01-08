#include "tree.h"

#include <stdlib.h>
#include "heap.h"

typedef struct Node {
	unsigned char symbol;
	uint64_t freq;
	struct Node* left;
	struct Node* right;
} node_t;

node_t* node_init(unsigned char symbol, uint64_t frequency) {
	node_t* new = malloc(sizeof(node_t));
	new->freq = frequency;
	new->symbol = symbol;
	new->left = NULL;
	new->right = NULL;
	return new;
}

int node_comparator(const void* a, const void* b) {
	// for min heap
	node_t* na = (node_t*)a;
	node_t* nb = (node_t*)b;
	if (na->freq > nb->freq)
		return -1;
	else if (na->freq < nb->freq)
		return 1;
	return 0;
}

node_t* build_huffman_tree(uint64_t freq[256]) {
	heap_t* heap = heap_init(256, node_comparator);
	// put every thing in heap
	for (int i = 0; i < 256; i++) {
		if (freq[i] > 0) {
			node_t* node = node_init(i, freq[i]);
			heap_push(heap, node);
		}
	}

	// build tree
	while (!is_size_one(heap)) {
		node_t* left = heap_pop(heap);
		node_t* right = heap_pop(heap);
		node_t* top = node_init(0, left->freq + right->freq);
		top->left = left;
		top->right = right;
		heap_push(heap, top);
	}
	return heap_top(heap);
}
