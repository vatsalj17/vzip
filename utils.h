#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>

#include "huffman.h"

void swap(void** a, void** b);
void print_codes(huff_code table[256], uint64_t freq[256]);
void print_help();

#endif
