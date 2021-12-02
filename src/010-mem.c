#include <stdlib.h>

typedef unsigned char byte_t;

typedef struct mem_t {
	struct mem_t* self;
	struct mem_t* next;
	struct mem_t* prev;
	size_t size;
	size_t len;
	byte_t* data;
} mem_t;

const size_t header_size = sizeof(mem_t);
const size_t mem_def_size = header_size << 1;

static inline void* mem_alloc_real(size_t size) {
	void* mem = calloc(size, 1);
	if (!mem) {
		throw(error.malloc);
	}
	return mem;
}

static inline void mem_init(mem_t** first) {
	register mem_t* mem = mem_alloc_real(mem_def_size);
	if (!mem)
		return;
	mem->self = mem;
	mem->next = NULL;
	mem->prev = NULL;
	mem->size = header_size;
	mem->len = header_size;
	mem->data = NULL;
	*first = mem;
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
	mem_t* next = mem_alloc_real(alloc_size);
	if (!next)
		return NULL;
	next->self = next;
	next->next = NULL;
	next->size = size;
	next->len = size;
	next->data = (byte_t*) next + header_size;
	next->prev = prev;
	prev->next = next;
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
	if (mem->next) {
		mem_t* last = mem_last(NULL);
		while (last->next) {
			last = last->next;
		}
		mem_t* prev = mem->prev;
		mem_t* next = mem->next;
		prev->next = next;
		next->prev = prev;
		last->next = mem;
		mem->prev = last;
		mem->next = NULL;
	}
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

byte_t* buffer_alloc(size_t size) {
	mem_t* mem = mem_alloc(size);
	if (mem) {
		return mem->data;
	} else {
		throw(error.malloc);
		return NULL;
	}
}

void buffer_free(byte_t* buffer) {
	if (!buffer)
		return;
	mem_free((mem_t*)((size_t) buffer - header_size));
}
