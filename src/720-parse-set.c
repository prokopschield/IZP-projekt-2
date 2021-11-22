set_t* parse_set(array_t* error, set_t* universe, FILE* input, bool EOL) {
	set_t* s = empty_set();
	while (!EOL) {
		string_t e_str = read_word(input, &EOL);
		int i = 0;
		element_t* e = get_element_by_str(&e_str, &i);
		str_free(&e_str);
		if (is_element_in_set(e, s)) {
			arr_push(error, "Duplicate element in set!");
		}
		if (universe && !is_element_in_set(e, universe)) {
			arr_push(error, "Element not in universe!");
		}
		add_element_to_set(e, &s);
	}
	return s;
}
