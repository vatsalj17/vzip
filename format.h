#ifndef FORMAT_H
#define FORMAT_H

#include <stdint.h>
#include <stdio.h>

#define MAGIC "VZIP"

typedef struct __attribute__((packed)) {
    uint8_t  magic[4];
    uint64_t original_size;
    uint32_t table_size;
} Header;

void enforce_metadata(FILE* file, uint64_t freq[256]);

#endif
