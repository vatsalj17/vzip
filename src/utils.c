#include "utils.h"
#include <stdio.h>

void swap(void** a, void** b) {
    void* temp = *a;
    *a = *b;
    *b = temp;
}

void print_codes(huff_code table[256], uint64_t freq[256]) {
	printf("Codes:- \n");
	for (int i = 0; i < 256; i++) {
		if (table[i].length) {
			printf("%03d => %c: ", i, (unsigned char)i);
			for (int j = table[i].length - 1; j >= 0; j--) {
				putchar((table[i].bits & (1u << j)) ? '1' : '0');
			}
            printf(" (%lu)\n", freq[i]);
		}
	}
}

void print_help() {
    printf("Usage: vzip [OPTION] <FILE>\n\n");
    printf("Options:\n");
    printf("  -c, --compress    Compress <FILE> to <FILE>.vzip\n");
    printf("  -d, --decompress  Decompress <FILE>.vzip to original file\n");
    printf("  -h, --help        Show this help message\n");
}
