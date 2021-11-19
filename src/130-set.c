array_t* all_sets() {
	static array_t* all_sets = NULL;
	if (!all_sets) {
		all_sets = arr_alloc(1);
		set_t* empty_set = (set_t*) buffer_alloc(sizeof(set_t));
		empty_set->line = 0;
		empty_set->number_of_elements = 0;
		empty_set->elements = NULL;
		empty_set->checksum.sum = 0;
		empty_set->checksum.product = 0;
		arr_push(all_sets, empty_set);
	}
	return all_sets;
}

set_t* empty_set() { return all_sets()->items[0]; }

bool is_element_in_set(element_t* element, set_t* set) {
	register size_t a = 0;
	register size_t b = set->number_of_elements - 1;
	register size_t c;
	register size_t euid = element->uid;
	// binary search
	while (c = ((b - a) >> 1) + a, a != b) {
		if (element == set->elements[c]) {
			return true;
		} else if (euid > set->elements[c]->uid) {
			a = c;
		} else {
			b = c;
		}
	}
	return element == set->elements[c];
}

set_t* expand_set(element_t* element, set_t* set) {
	if (is_element_in_set(element, set)) {
		return set;
	}
	array_t* sets = all_sets();
	size_t new_length = set->number_of_elements + 1;
	size_t new_sum = set->checksum.sum + element->uid;
	size_t new_product = set->checksum.product * element->uid;
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
	element_t** element_list =
			(element_t**) buffer_alloc((sizeof(element_t*) * new_length));
	bool flag = false;
	size_t i = 0;
	for (; i < set->number_of_elements;) {
		if (set->elements[i]->uid < element->uid) {
			element_list[i + flag] = set->elements[i];
			++i;
		} else {
			element_list[i] = element;
			flag = true;
		}
	}
	set_t* new_set = (set_t*) buffer_alloc(sizeof(set_t));
	new_set->number_of_elements = new_length;
	new_set->checksum.sum = new_sum;
	new_set->checksum.product = new_product;
	new_set->elements = element_list;
	arr_push(sets, new_set);
	return new_set;
}

void add_element_to_set(element_t* element, set_t** set) {
	expand_set(element,* set);
}

void set_print(set_t* set, FILE* stream) {
	putc('S', stream);
	for (size_t i = 0; i < set->number_of_elements; ++i) {
		element_print(set->elements[i], stream);
	}
	putc('\n', stream);
}
