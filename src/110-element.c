array_t* all_elements() {
	static array_t* all_elements = NULL;
	if (!all_elements) {
		all_elements = arr_alloc(1);
		if (!all_elements) {
			throw(error.malloc);
			return NULL;
		}
		arr_push(all_elements, NULL); // start numbering at 1
	}
	return all_elements;
}

element_t* get_element_by_uid(size_t uid) { return all_elements()->items[uid]; }

element_t* get_element_by_str(string_t* str, int* index) {
	string_t el_str = strop_read_word(str, index);
	array_t* elements = all_elements();
	if (!el_str.len || !elements) {
		throw_error("Element allocation failed: '%s'", &str->data[*index]);
		return NULL;
	}
	for (size_t i = 1; i < elements->len; ++i) {
		element_t* e = elements->items[i];
		if (str_equal(&el_str, &e->str)) {
			str_free(&el_str); // goes out of scope
			return e;
		}
	}
	element_t* new_element = (element_t*) buffer_alloc(sizeof(element_t));
	if (!new_element) {
		throw_error("Could not allocate new element '%s'.", el_str.data);
		str_free(&el_str); // exists, tested previously
		return NULL;
	}
	new_element->uid = elements->len;
	new_element->str = el_str;
	arr_push(elements, new_element);
	return new_element;
}

void element_print(element_t* element, FILE* stream) {
	str_print(&element->str, stream);
}
