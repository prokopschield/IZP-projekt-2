#include <stdbool.h>

array_t* all_sets() {
	static array_t* all_sets = NULL;
	if (!all_sets) {
		all_sets = arr_alloc(1);
		if (!all_sets) {
			throw(error.malloc);
			return NULL;
		}
		set_t* empty_set = (set_t*) buffer_alloc(sizeof(set_t));
		if (!empty_set) {
			throw(error.malloc);
			return NULL;
		}
		empty_set->line = 0;
		empty_set->number_of_elements = 0;
		empty_set->elements = NULL;
		empty_set->checksum.sum = 0;
		empty_set->checksum.product = 1;
		arr_push(all_sets, empty_set);
	}
	return all_sets;
}

set_t* empty_set() {
	register array_t* sets = all_sets();
	return sets ? (sets->items ? sets->items[0] : NULL) : NULL;
}

bool is_element_in_set(element_t* restrict element, set_t* restrict set) {
	if (!element || !set || !set->number_of_elements)
		return false;
	register size_t a = 0;
	register size_t b = set->number_of_elements - 1;
	register size_t c;
	// binary search
	while (c = ((b - a) >> 1) + a, a < b) {
		if (element == set->elements[c]) {
			return true;
		} else if (element->uid > set->elements[c]->uid) {
			a = c + 1;
		} else {
			b = c ? (c - 1) : 0;
		}
	}
	return element == set->elements[c];
}

set_t* expand_set(element_t* element, set_t* set) {
	if (!element || is_element_in_set(element, set)) {
		return set;
	}
	array_t* sets = all_sets();
	if (!sets) {
		throw(error.malloc);
		return NULL;
	}
	size_t new_length = set->number_of_elements + 1;
	size_t new_sum = set->checksum.sum + (size_t) element->uid;
	size_t new_product = set->checksum.product * (size_t) element->uid;
	for (size_t i = 1; i < sets->len; ++i) {
		set_t* s = (set_t*) sets->items[i];
		if ((new_length != s->number_of_elements)) {
			continue;
		}
		if ((new_sum != s->checksum.sum) || (new_product != s->checksum.product)) {
			continue;
		}
		return s;
	}
	// set does not exist already
	register const size_t alloc_size = (sizeof(element_t*) * new_length);
	element_t** element_list = (element_t**) buffer_alloc(alloc_size);
	if (!element_list) {
		throw(error.malloc);
		return NULL;
	}

	// add element, sort by uid
	for (size_t i_o = 0, i_n = 0; i_n < new_length; ++i_n) {
		element_list[i_n] =
				((i_o < set->number_of_elements) // empty set would segfault
				 && ((i_o != i_n) || (element->uid > set->elements[i_o]->uid)))
						? set->elements[i_o++]
						: element;
	}

	set_t* new_set = (set_t*) buffer_alloc(sizeof(set_t));
	if (!new_set) {
		throw(error.malloc);
		return NULL;
	}
	new_set->number_of_elements = new_length;
	new_set->checksum.sum = new_sum;
	new_set->checksum.product = new_product;
	new_set->elements = element_list;
	arr_push(sets, new_set);
	return new_set;
}

void add_element_to_set(element_t* element, set_t** set) {
	register set_t* new_set = expand_set(element, *set);
	if (new_set) {
		*set = new_set;
	}
}

void set_print(set_t* set, FILE* stream, bool is_universe) {
	putc(is_universe ? 'U' : 'S', stream);
	for (size_t i = 0; i < set->number_of_elements; ++i) {
		putc(' ', stream);
		element_print(set->elements[i], stream);
	}
	putc('\n', stream);
}
