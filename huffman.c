#include "huffman.h"

#include <stdint.h>
#include <stdio.h>

#include "tree.h"

typedef struct HuffCode {
	uint32_t bits;
	uint8_t length;
} huff_code;

void build_frequency_table(FILE* file, uint64_t freq[256]) {
	unsigned char c;
	while (fread(&c, 1, 1, file) == 1) {
		freq[c]++;
	}
}

void build_code_table(node_t* root, huff_code table[256], uint32_t code, int level) {
}
