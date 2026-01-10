#include "compress.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fileio.h"
#include "huffman.h"
// #include "utils.h"

void compress(const char* input_file, const char* output_file) {
	FILE* fi = fopen(input_file, "rb");
	if (!fi) {
		fprintf(stderr, "fopen: %s couldn't be opened\n", input_file);
		return;
	}
	printf("Compressing %s to %s .....", input_file, output_file);

	uint64_t freq[256] = {0};
	build_frequency_table(fi, freq);
	node_t* tree = build_huffman_tree(freq);
	huff_code table[256] = {0};
	build_code_table(tree, table, 0, 0);
	free_tree(tree);
	// print_codes(table, freq);
	FILE* fo = fopen(output_file, "wb");
	bit_writer* bw = bw_init(fo);
	enforce_metadata(bw, fi, freq);
	write_codes(bw, fi, table);

	fclose(fi);
	fclose(fo);
	free(bw);
}

void decompress(const char* compressed_file, const char* output_file) {
	FILE* fc = fopen(compressed_file, "rb");
	if (!fc) {
		fprintf(stderr, "fopen: %s couldn't be opened\n", compressed_file);
		return;
	}
	char* magic = calloc(4, sizeof(char));
	fread(magic, sizeof(char), 4, fc);
	if (strcmp(magic, MAGIC) != 0) {
		fprintf(stderr, "error: wrong filetype provided!\n");
		free(magic);
		return;
	}
	printf("Decompressing %s to %s .....", compressed_file, output_file);
	uint64_t orig_size;
	fread(&orig_size, sizeof(uint64_t), 1, fc);
	uint64_t freq[256];
	fread(freq, sizeof(uint64_t), 256, fc);
	node_t* tree = build_huffman_tree(freq);
    // printtree(tree, 0);
	bit_reader* br = br_init(fc);

	FILE* fo = fopen(output_file, "wb");
	write_orig_bytes(br, fo, tree, orig_size);

	free(br);
	free(magic);
	free_tree(tree);
	fclose(fc);
	fclose(fo);
}
