#include <stdint.h>
#include <stdio.h>

#include "huffman.h"

int main(int argc, char** argv) {
	if (argc < 2) {
		fprintf(stderr, "usage: %s <filename>\n", argv[0]);
		return 1;
	}
	FILE* f = fopen(argv[1], "r");
	if (!f) {
		fprintf(stderr, "fopen: %s couldn't be opened\n", argv[1]);
		return 1;
	}
	uint64_t freq[256] = {0};
	build_frequency_table(f, freq);
	for (int i = 0; i < 256; i++) {
		if (freq[i])
			printf("%d => %c: %lu\n", i, (unsigned char)i, freq[i]);
	}
	fclose(f);
}
