#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "compress.h"

int main(int argc, char** argv) {
	if (argc < 2) {
		fprintf(stderr, "usage: %s <filename>\n", argv[0]);
		return 1;
	}
	char* extension = "vzip";
    size_t size = strlen(argv[1]) + strlen(extension) + 2;
	char* output_file = calloc(size, sizeof(char));
    snprintf(output_file, size, "%s.%s", argv[1], extension);
	compress(argv[1], output_file);
    free(output_file);
}
