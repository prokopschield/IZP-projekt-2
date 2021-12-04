rel_t* parse_rel(set_t* universe, FILE* input, bool EOL) {

	// start with empty rel
	rel_t* rel = empty_rel();

	while (!EOL) {
		string_t e_str = read_word(input, &EOL);
		int i = 1; // skip '('
		element_t* L = get_element_by_str(&e_str, &i);
		str_free(&e_str);

		e_str = read_word(input, &EOL);
		e_str.data[--e_str.len] = 0; // erase ')'
		i = 0;
		element_t* R = get_element_by_str(&e_str, &i);
		str_free(&e_str);

		// check if element allocation failed
		if (!L || !R) {
			throw(error.malloc);
			return rel;
		}

		if (universe && !is_element_in_set(L, universe)) {
			throw_chars("Element ");
			element_print(L, stderr);
			fprintf(stderr, " not in Universe ");
			set_print(universe, stderr, true);
		}

		if (universe && !is_element_in_set(R, universe)) {
			throw_chars("Element ");
			element_print(R, stderr);
			fprintf(stderr, " not in Universe ");
			set_print(universe, stderr, true);
		}

		pair_t* pair = get_pair(L, R);
		if (!pair) {
			throw(error.malloc);
			return rel;
		}

		if (is_pair_in_rel(pair, rel)) {
			throw_chars("Duplicate element: ");
			pair_print(pair, stderr);
			fprintf(stderr, " is already in ");
			rel_print(rel, stderr, false);
		}

		add_pair_to_rel(pair, &rel);
	}
	return rel;
}
