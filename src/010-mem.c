#include <malloc.h>

typedef unsigned char byte_t;

typedef struct mem_t {
	byte_t* self;
	byte_t* next;
	size_t size;
	size_t len;
	byte_t* data;
} mem_t;

const size_t header_size = sizeof(mem_t);
const size_t mem_def_size = header_size << 1;

void mem_init(mem_t** first) {
	byte_t* buffer = malloc(mem_def_size);
	for (size_t i = 0; i < mem_def_size; ++i) {
		buffer[i] = 0;
	}
	*first = (mem_t*) buffer;
	(*first)->self = buffer;
	(*first)->next = NULL;
	(*first)->size = header_size;
	(*first)->len = header_size;
	(*first)->data = NULL;
}

mem_t* mem_first() {
	static mem_t* first = NULL;
	if (!first) mem_init(&first);
	return first;
}

mem_t* mem_new(mem_t* prev, size_t size) {
	while (prev->next && ((mem_t*) prev->next != prev)) {
		prev = (mem_t*) prev->next;
	}
	const size_t alloc_size = size + mem_def_size;
	byte_t* buffer = malloc(alloc_size);
	for (size_t i = 0; i < alloc_size; ++i) {
		buffer[i] = 0;
	}
	mem_t* next = (mem_t*) buffer;
	next->self = buffer;
	next->next = NULL;
	next->size = size;
	next->len = size;
	next->data = (byte_t*) next + header_size;
	prev->next = (byte_t*) next;
	return next;
}

mem_t* mem_seek(mem_t* prev, size_t size) {
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

mem_t* mem_alloc(size_t size) {
	return mem_seek(mem_first(), size);
}

void mem_free(mem_t* mem) {
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
	return mem_alloc(size)->data;
}

void buffer_free(byte_t* buffer) {
	mem_free(
		(mem_t*) (
			(size_t) buffer - header_size
		)
	);
}
