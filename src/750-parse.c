void parse(set_t* universe, array_t* lines, FILE* input) {
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
		line->val_set = parse_set(universe, input, EOL);
		line->line_type = line_type_set;
		break;
	}
	case 'R': {
		line->val_rel = parse_rel(universe, input, EOL);
		line->line_type = line_type_rel;
		break;
	}
	case 'C': {
		line->val_cmd = parse_cmd(input, EOL);
		line->line_type = line_type_cmd;
		break;
	}
	default: {
		throw_error("Unknown line type: '%s'", type_str.data);
	}
	}

	arr_push(lines, line);
}
