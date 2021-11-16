#include <stdio.h>

void clear_whitespace(FILE* file) {
	register int c = 0;
	for (c = getc(file); c == ' ' || c == '\t' || c == '\r' || c == '\n'; c = getc(file));
	if (c != EOF) ungetc(c, file);
}

string_t str_readline(FILE* file) {
	fpos_t fpos;
	fgetpos(file, &fpos);
	size_t len = 0;
	for (int c = getc(file); c != '\n' && c != '\r' && c != EOF; c = getc(file)) ++len;
	fsetpos(file, &fpos);
	mem_t* mem = mem_alloc(len + 1);
	for (size_t i = 0; i < len; ++i) {
		mem->data[i] = getc(file);
	}
	clear_whitespace(file); // remote trailing \n
	mem->data[len] = 0; // null-terminate string
	string_t str = { mem, len, mem->data };
	return str;
}
