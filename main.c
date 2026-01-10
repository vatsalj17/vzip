#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "compress.h"
#include "utils.h"

int main(int argc, char** argv) {
	if (argc >= 2 && (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help"))) {
		print_help();
		return 0;
	}
	if (argc != 3) {
		fprintf(stderr, "usage: %s [options] <filename>\n", argv[0]);
		return 1;
	}
	char* input_file = strdup(argv[2]);
	if (strcmp(argv[1], "-c") == 0 || strcmp(argv[1], "--compress") == 0) {
		char* extension = "vzip";
		size_t size = strlen(input_file) + strlen(extension) + 2;
		char* output_file = calloc(size, sizeof(char));
		snprintf(output_file, size, "%s.%s", input_file, extension);
		compress(input_file, output_file);
		free(output_file);
	} else if (strcmp(argv[1], "-d") == 0 || strcmp(argv[1], "--decompress") == 0) {
		size_t size = strlen(input_file) - 5;
		char* output_file = calloc(size + 1, sizeof(char));
		strncpy(output_file, input_file, size);
		decompress(input_file, output_file);
		free(output_file);
	} else {
		printf("Invalid argument\n");
		free(input_file);
		return 1;
	}
	free(input_file);
	return 0;
}
