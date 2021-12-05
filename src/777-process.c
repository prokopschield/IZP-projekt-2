int process(FILE* input, FILE* output) {
	if (!empty_set() || !empty_rel()) {
		throw_error("Empty set/rel allocation failed. [%p, %p]", (void*) empty_set(), (void*) empty_rel());
	}
	array_t lines = line_array_init();
	size_t line_i = 1;
	while (!error.any && !feof(input)) {
		parse(lines.len > 1 ? (((line_t*) lines.items[1])->val_set) : NULL, &lines, input);
	}
	input_tests();
	while (!error.any && (line_i < lines.len)) {
		execute(&lines, &line_i, output);
	}
	if (error.malloc) {
		throw_chars("Memory allocation error.\n");
	}
	if (error.any) {
		throw_error("Execution terminated on line %ld.\n", line_i);
	}
	return error.any;
}
