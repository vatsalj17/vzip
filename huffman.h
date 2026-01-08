#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stdint.h>
#include <stdio.h>

void build_frequency_table(FILE* file, uint64_t freq[256]);

#endif
