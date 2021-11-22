rel_t* parse_rel(array_t* error, set_t* universe, FILE* input, bool EOL) {
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
		if (universe && !is_element_in_set(L, universe)) {
			arr_push(error, "Element not in universe!");
		}
		if (universe && !is_element_in_set(R, universe)) {
			arr_push(error, "Element not in universe!");
		}
		pair_t* pair = get_pair(L, R);
		if (is_pair_in_rel(pair, rel)) {
			arr_push(error, "Duplicate pair in relation!");
		}
		add_pair_to_rel(pair, &rel);
	}
	return rel;
}
