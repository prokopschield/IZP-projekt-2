void execute(array_t* error, array_t* lines, size_t* line_i, FILE* output) {
	line_t* line = lines->items[*line_i];
	const bool bval = line->val_cmd && eval(error, lines->items[1], line);
	if (line->val_set) {
		set_print(line->val_set, output);
	} else if (line->val_rel) {
		rel_print(line->val_rel, output);
	} else {
		fputs(bval ? "true\n" : "false\n", output);
	}
	if (!error->len) {
		++*line_i;
	}
}
