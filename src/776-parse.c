string_t read_word(FILE* stream, bool* EOL) {
	static int length = 0;
	static char buffer[READ_BUFFER_LENGTH] = { 0 };
	do {
		while ((buffer[length++] = getc(stream)) > ' ');
		if (buffer[--length] == '\n')
			*EOL = true;
		buffer[length] = 0; // null-terminate string
	} while (!length && !feof(stream));
	string_t str = str_alloc(length);
	for (int i = 0; i <= length; ++i) {
		str.data[i] = buffer[i];
	}
	length = 0;
	while ((buffer[length++] = getc(stream)) <= ' ') {
		if (buffer[--length] == EOF) {
			*EOL = true;
			break;
		} else if (buffer[length] == '\n') {
			*EOL = true;
		}
	}
	return str;
}

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

void parse(array_t* error, set_t* universe, array_t* lines, FILE* input) {
	bool EOL = false;
	const string_t type_str = read_word(input, &EOL);

	line_t* line = (line_t*) buffer_alloc(sizeof(line_t));
	line->line = lines->len;
	line->val_set = NULL;
	line->val_rel = NULL;
	line->val_cmd = NULL;

	switch (type_str.data[0]) {
	case 'U':
	case 'S': {
		line->val_set = parse_set(error, universe, input, EOL);
		line->line_type = line_type_set;
		break;
	}
	case 'R': {
		line->val_rel = parse_rel(error, universe, input, EOL);
		line->line_type = line_type_rel;
		break;
	}
	default: {
		char* e_str = (char*) buffer_alloc(MAX_ELEMENT_LENGTH + 24);
		sprintf(e_str, "Unknown line type: '%s'", type_str.data);
		arr_push(error, e_str);
	}
	}

	arr_push(lines, line);
}
