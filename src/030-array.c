#include <stdbool.h>

#define arr_align 4

typedef struct array_t {
	size_t size;
	size_t len;
	void** items;
} array_t;

array_t* arr_alloc(size_t size) {
	array_t* arr = (array_t*) buffer_alloc(sizeof(array_t));
	if (!arr) return NULL;
	arr->size = size;
	arr->len = 0;
	arr->items = (void**) buffer_alloc(size * sizeof(size_t));
	if (!arr->items) {
		buffer_free((byte_t*) arr);
		return NULL;
	}
	return arr;
}

void arr_free(array_t* arr) {
	arr->size = 0;
	arr->len = 0;
	buffer_free((byte_t*) arr->items);
	arr->items = NULL;
	buffer_free((byte_t*) arr);
}

bool arr_push(array_t* arr, void* item) {
	if (arr->len < arr->size) {
		arr->items[arr->len++] = item;
		return true;
	}
	size_t new_size = (((arr->size >> arr_align) + 1) << arr_align);
	void** new_items = (void**) buffer_alloc(new_size * sizeof(size_t));
	if (!new_items) return false;
	for (size_t i = 0; i < arr->len; ++i) {
		new_items[i] = arr->items[i];
	}
	buffer_free((byte_t*) arr->items);
	arr->items = new_items;
	arr->size = new_size;
	return arr_push(arr, item);
}

void* arr_pop(array_t* arr) {
	return arr->items[--arr->len];
}