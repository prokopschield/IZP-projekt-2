#include <stdlib.h>

typedef unsigned char byte_t;

typedef struct mem_t {
	byte_t* self;
	byte_t* next;
	byte_t* prev;
	size_t size;
	size_t len;
	byte_t* data;
} mem_t;

const size_t header_size = sizeof(mem_t);
const size_t mem_def_size = header_size << 1;

void mem_zero(size_t* p, size_t b) {
	register size_t n = b / sizeof(size_t);
	for (size_t i = 0; i < n; ++i) {
		p[i] = 0L;
	}
}

void mem_init(mem_t** first) {
	byte_t* buffer = malloc(mem_def_size);
	if (!buffer)
		return;
	mem_zero((size_t*) buffer, mem_def_size);
	*first = (mem_t*) buffer;
	(*first)->self = buffer;
	(*first)->next = NULL;
	(*first)->prev = NULL;
	(*first)->size = header_size;
	(*first)->len = header_size;
	(*first)->data = NULL;
}

mem_t* mem_first() {
	static mem_t* first = NULL;
	if (!first)
		mem_init(&first);
	return first;
}

mem_t* mem_last(mem_t* replace) {
	static mem_t* last = NULL;
	return replace ? (last = replace) : (last ? last : (last = mem_first()));
}

mem_t* mem_new(mem_t* prev, size_t size) {
	while (prev->next && ((mem_t*) prev->next != prev)) {
		prev = (mem_t*) prev->next;
	}
	const size_t alloc_size =
			((((size + mem_def_size - 1) >> sizeof(size_t)) + 1) << sizeof(size_t));
	byte_t* buffer = malloc(alloc_size);
	if (!buffer)
		return NULL;
	mem_zero((size_t*) buffer, alloc_size);
	mem_t* next = (mem_t*) buffer;
	next->self = buffer;
	next->next = NULL;
	next->size = size;
	next->len = size;
	next->data = (byte_t*) next + header_size;
	next->prev = (byte_t*) prev;
	prev->next = (byte_t*) next;
	return next;
}

mem_t* mem_alloc(size_t size) {
	register mem_t* prev = mem_last(NULL);
	if (!prev)
		return NULL; // mem_init() -> malloc() failed
	while (prev->len && prev->next) {
		prev = (mem_t*) prev->next;
	}
	mem_last(prev);
	while (1) {
		if (!prev->len && (prev->size >= size)) {
			prev->len = size;
			return prev;
		} else if (prev->next) {
			prev = (mem_t*) prev->next;
		} else {
			return mem_new(prev, size);
		}
	}
}

void mem_free(mem_t* mem) {
	if (!mem)
		return;
	mem_t* last = mem_last(NULL);
	while (last->next) {
		last = (mem_t*) last->next;
	}
	mem_t* prev = (mem_t*) mem->prev;
	mem_t* next = (mem_t*) mem->next;
	prev->next = (byte_t*) next;
	next->prev = (byte_t*) prev;
	last->next = (byte_t*) mem;
	mem->prev = (byte_t*) last;
	mem->next = NULL;
	mem->len = 0;
}

void mem_free_everything() {
	register mem_t* frst = mem_first();
	register mem_t* scnd = (mem_t*) frst->next;
	if (!scnd) {
		free(frst);
		return;
	}
	while (scnd->next) {
		free(frst);
		frst = scnd;
		scnd = (mem_t*) scnd->next;
	}
	free(frst);
	free(scnd);
}

byte_t* buffer_alloc(size_t size) { return mem_alloc(size)->data; }

void buffer_free(byte_t* buffer) {
	if (!buffer)
		return;
	mem_free((mem_t*)((size_t) buffer - header_size));
}
