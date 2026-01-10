#ifndef FILE_H
#define FILE_H

#include <stdint.h>
#include <stdio.h>

#include "huffman.h"

#define MAGIC "VZIP"

typedef struct __attribute__((packed)) {
	uint8_t magic[4];
	uint64_t original_size;
} Header;

typedef struct BitWriter bit_writer;
typedef struct BitReader bit_reader;

bit_writer* bw_init(FILE* fp);
bit_reader* br_init(FILE* fp);
void enforce_metadata(bit_writer* bw, FILE* file, uint64_t freq[256]);
void write_codes(bit_writer* bw, FILE* input, huff_code table[256]);
void write_orig_bytes(bit_reader* br, FILE* output, node_t* root, uint64_t file_size);

#endif
