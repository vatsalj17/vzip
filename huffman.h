#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

typedef struct Node {
	unsigned char symbol;
	uint64_t freq;
	struct Node* left;
	struct Node* right;
} node_t;

typedef struct HuffCode {
	uint32_t bits;
	uint8_t length;
} huff_code;

node_t* node_init(unsigned char symbol, uint64_t frequency);
node_t* build_huffman_tree(uint64_t freq[256]);
bool is_leaf(node_t* n);
void printtree(node_t* root, int level);

void build_frequency_table(FILE* file, uint64_t freq[256]);
void build_code_table(node_t* root, huff_code table[256], uint32_t code, int level);
void free_tree(node_t* root);

#endif
