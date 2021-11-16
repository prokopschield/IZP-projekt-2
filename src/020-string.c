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
