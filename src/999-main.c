#include <errno.h>
#include <stdio.h>
#include <string.h>

int main(int argc, const char* restrict argv[]) {
	if (argc < 2) {
		fprintf(stderr, "Usage: %s FILE\n", argv[0]);
		return EXIT_FAILURE;
	}
	FILE* input = fopen(argv[1], "r");
	if (!input) {
		fprintf(stderr, "Error whilst opening %s: %s\n", argv[1], strerror(errno));
		return EXIT_FAILURE;
	}
	int ret = process(input, stdout);
	fclose(input);
	// Remember to free everything!!!
	mem_free_everything();
	return ret;
}
