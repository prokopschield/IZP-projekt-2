#include <stdio.h>

#define str_readline_buffer 1024
#define str_readline_maxlen 1000

typedef struct string_t {
	mem_t* mem;
	size_t len;
	byte_t* data;
} string_t;

string_t str_alloc(size_t len) {
	mem_t* mem = mem_alloc(len + 1);
	byte_t* data = mem->data;
	string_t str = { mem, len, data };
	return str;
}

string_t* str_palloc(size_t len) {
	mem_t* mem = mem_alloc(len + sizeof(string_t) + 1);
	string_t* str = (string_t*) mem->data;
	str->mem = mem;
	str->len = len;
	str->data = mem->data + sizeof(string_t);
	return str;
}

void str_free(string_t* str) {
	register mem_t* mem = str->mem;
	str->mem = NULL;
	str->len = 0;
	str->data = NULL;
	mem_free(mem);
}

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
	mem_t* mem = mem_alloc(len);
	for (size_t i = 0; i < len; ++i) {
		mem->data[i] = getc(file);
	}
	clear_whitespace(file); // remote trailing \n
	mem->data[len] = 0; // null-terminate string
	string_t str = { mem, len, mem->data };
	return str;
}
