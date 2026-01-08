#include "huffman.h"

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

bool is_leaf(node_t* n) {
    if (n->left == NULL && n->right == NULL) return true;
    return false;
}

void build_frequency_table(FILE* file, uint64_t freq[256]) {
	unsigned char c;
	while (fread(&c, 1, 1, file) == 1) {
		freq[c]++;
	}
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
        printtree(heap_top(heap), 0);
	}
	return heap_top(heap);
}

void printtree(node_t* root, int level) {
    if (!root) return;
    for (int i = 0; i < level; i++) printf("  ");
    printf("\'%d:%c %lu\' \n", root->symbol, root->symbol, root->freq);
    printtree(root->left, level + 1);
    printtree(root->right, level + 1);
}

void build_code_table(node_t* root, huff_code table[256], uint32_t code, int level) {
    if (!root) return;
    if (is_leaf(root)) {
        table[root->symbol].bits = code;
        table[root->symbol].length = level;
        return;
    }
    // left => 0
    build_code_table(root->left, table, code << 1, level + 1);
    // right => 1
    build_code_table(root->right, table, (code << 1) | 1, level + 1);
}
