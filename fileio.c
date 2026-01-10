#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"

typedef struct BitWriter {
	FILE* fp;
	uint8_t buffer;
	uint8_t count;
} bit_writer;

bit_writer* bw_init(FILE* fp) {
	bit_writer* new = malloc(sizeof(bit_writer));
	if (!new) return NULL;
	new->fp = fp;
	new->buffer = 0;
	new->count = 0;
	return new;
}

void write_bit(bit_writer* bw, uint8_t bit) {
	bw->buffer = (bw->buffer << 1) | (bit & 1);
	bw->count++;
	if (bw->count >= 8) {
		fwrite(&bw->buffer, 1, 1, bw->fp);
		bw->buffer = 0;
		bw->count = 0;
	}
}

void bw_flush(bit_writer* bw) {
	if (bw->count == 0) return;
	bw->buffer = bw->buffer << (8 - bw->count);
	fwrite(&bw->buffer, 1, 1, bw->fp);
	bw->buffer = 0;
	bw->count = 0;
}

void write_codes(bit_writer* bw, FILE* input, huff_code table[256]) {
    int ch = fgetc(input);
    while (ch != EOF) {
        huff_code code = table[ch];
        for (int i = code.length - 1; i >= 0; i--) {
            uint8_t bit = (1u << i) & code.bits;
            write_bit(bw, bit);
        }
        ch = fgetc(input);
    }
    bw_flush(bw);
}
