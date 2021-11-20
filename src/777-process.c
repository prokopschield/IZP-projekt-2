int process(FILE* input, FILE* output) {
	array_t lines = {0, 0, NULL};
	line_t line_zero = {0, line_type_set, empty_set(), NULL, 0, {NULL, 0, NULL}};
	arr_push(&lines, &line_zero);
	array_t error = {0, 0, NULL};
	size_t line_i = 0;
	while (!error.len && (!feof(input) || (line_i < lines.len))) {
		while (line_i >= lines.len) {
			line_t* line = (line_t*) buffer_alloc(sizeof(line_t));
			line->line = line_i;
			line->line_type = line_type_undefined;
			line->val_set = NULL;
			line->val_rel = NULL;
			line->val_bool = 0;
			line->input = str_readline(input);
			arr_push(&lines, line);
		}
		execute(&error, &lines, &line_i, output);
	}
	if (error.len) {
		fprintf(stderr, "Error! ");
		for (size_t i = 0; i < error.len; ++i) {
			fprintf(stderr, "%s\n", (char*) error.items[i]);
		}
		fprintf(stderr, "Execution terminated on line %ld.\n", line_i);
	}
	return error.len;
}
