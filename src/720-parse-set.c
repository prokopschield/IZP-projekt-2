set_t* parse_set(set_t* universe, FILE* input, bool EOL) {
	set_t* s = empty_set();
	while (!EOL) {
		string_t e_str = read_word(input, &EOL);
		int i = 0;
		element_t* e = get_element_by_str(&e_str, &i);
		str_free(&e_str);
		if (is_element_in_set(e, s)) {
			throw_chars("Duplicate element: ");
			element_print(e, stderr);
			fprintf(stderr, " is already in ");
			set_print(s, stderr, false);
		}
		if (universe && !is_element_in_set(e, universe)) {
			throw_chars("Element ");
			element_print(e, stderr);
			fprintf(stderr, " not in Universe: ");
			set_print(universe, stderr, true);
		}
		add_element_to_set(e, &s);
	}
	return s;
}
