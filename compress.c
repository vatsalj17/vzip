#include "compress.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "fileio.h"
#include "huffman.h"
#include "utils.h"

void compress(const char* input_file, const char* output_file) {
	FILE* fi = fopen(input_file, "rb");
	if (!fi) {
		fprintf(stderr, "fopen: %s couldn't be opened\n", input_file);
		return;
	}
	uint64_t freq[256] = {0};
	build_frequency_table(fi, freq);
	node_t* tree = build_huffman_tree(freq);
	huff_code table[256] = {0};
	build_code_table(tree, table, 0, 0);
	free_tree(tree);
    print_codes(table, freq);
	FILE* fo = fopen(output_file, "wb");
	bit_writer* bw = bw_init(fo);
    enforce_metadata(bw, fi, freq);
    write_codes(bw, fi, table);
    fclose(fi);
    fclose(fo);
    free(bw);
}
