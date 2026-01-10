#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct Node  node_t;

typedef struct HuffCode {
	uint32_t bits;
	uint8_t length;
} huff_code;

node_t* node_init(unsigned char symbol, uint64_t frequency);
int node_comparator(const void* a, const void* b);
node_t* build_huffman_tree(uint64_t freq[256]);
bool is_leaf(node_t* n);
void printtree(node_t* root, int level);

void build_frequency_table(FILE* file, uint64_t freq[256]);
void build_code_table(node_t* root, huff_code table[256], uint32_t code, int level);
void free_tree(node_t* root);

#endif
