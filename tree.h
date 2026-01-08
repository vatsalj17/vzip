#ifndef TREE_H
#define TREE_H

#include <stdint.h>

typedef struct Node  node_t;

node_t* node_init(unsigned char symbol, uint64_t frequency);
int node_comparator(const void* a, const void* b);
node_t* build_huffman_tree(uint64_t freq[256]);

#endif
