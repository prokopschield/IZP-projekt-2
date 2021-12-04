void execute(array_t* lines, size_t* line_i, FILE* output) {
	line_t* line = line_get(lines, *line_i);
	if (!line) {
		throw_error("Line %ld not loadable for some reason!", *line_i);
		return;
	}
	evaled_t evaled = eval(lines, line);
	if (evaled.s) {
		fprintf(output, "%s\n", evaled.s);
	} else if (evaled.u) { // if use flag is set
		fprintf(output, "%lld\n", evaled.n);
	} else if (line->val_set) {
		set_print(line->val_set, output, *line_i == 1);
	} else if (line->val_rel) {
		rel_print(line->val_rel, output, 0);
	} else {
		line_print(line, output);
	}
	if (!error.any) {
		if (evaled.N) {
			*line_i = evaled.N;
		} else {
			++*line_i;
		}
	}
}
