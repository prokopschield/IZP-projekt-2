int process(FILE* input, FILE* output) {
	if (!empty_set() || !empty_rel()) {
		throw_error("Empty set/rel allocation failed. [%p, %p]", (void*) empty_set(), (void*) empty_rel());
		return EXIT_FAILURE;
	}
	array_t lines = { 0, 0, NULL };
	line_t line_zero = { 0, line_type_set, empty_set(), NULL, NULL };
	arr_push(&lines, &line_zero);
	array_t error = { 0, 0, NULL };
	size_t line_i = 1;
	while (!error.len && (!feof(input) || (line_i < lines.len))) {
		while (line_i >= lines.len) {
			parse(&error, lines.len > 1 ? (((line_t*) lines.items[1])->val_set) : NULL, &lines, input);
		}
		execute(&lines, &line_i, output);
	}
	if (error.len) {
		for (size_t i = 0; i < error.len; ++i) {
			fprintf(stderr, "Error :: %s\n", (char*) error.items[i]);
		}
		fprintf(stderr, "Execution terminated on line %ld.\n", line_i);
	}
	return error.len;
}
