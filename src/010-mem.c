#include <malloc.h>

#define mem_def_size 1200
#define mem_min_size 800
#define mem_add_size 400

typedef unsigned char byte_t;

typedef struct {
	byte_t* self;
	byte_t* next;
	size_t size;
	size_t len;
	byte_t* data;
} mem_t;

const size_t header_size = sizeof(mem_t);

void mem_init(mem_t** first) {
	byte_t* buffer = malloc(mem_def_size);
	for (size_t i = 0; i < mem_def_size; ++i) {
		buffer[i] = 0;
	}
	*first = (mem_t*) buffer;
	(*first)->self = buffer;
	(*first)->next = NULL;
	(*first)->size = 0;
	(*first)->len = 0;
	(*first)->data = NULL;
}

void mem_alloc() {
	static mem_t* first = NULL;
	if (!first) mem_init(&first);
}
