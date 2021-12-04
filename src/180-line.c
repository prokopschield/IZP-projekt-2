extern line_t* line_init(array_t* lines);

array_t line_array_init() {
	array_t lines = { 0, 0, NULL };

	line_t* line_zero = line_init(&lines);
	if (!line_zero) {
		throw(error.malloc);
		return lines;
	}

	line_zero->val_set = empty_set();
	line_zero->val_rel = empty_rel();

	return lines;
}

line_t* line_init(array_t* lines) {
	line_t* line = (line_t*) buffer_alloc(sizeof(line_t));

	if (!line) {
		throw_error("Could not allocate line %ld", lines->len);
		return NULL;
	}

	line->line = lines->len;
	line->val_set = NULL;
	line->val_rel = NULL;
	line->val_cmd = NULL;

	if (!arr_push(lines, line)) {
		throw_error("Could not create line %ld", lines->len);
	}

	return line;
}

line_t* line_get(array_t* lines, size_t n) {
	if (n < lines->len) {
		return lines->items[n];
	} else {
		return NULL;
	}
}
