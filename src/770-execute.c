void execute(array_t* lines, size_t* line_i, FILE* output) {
	line_t* line = lines->items[*line_i];
	// const bool bval = line->val_cmd && eval(error, lines->items[1], line);
	if (line->val_set) {
		set_print(line->val_set, output, *line_i == 1);
	} else if (line->val_rel) {
		rel_print(line->val_rel, output, 0);
	} else {
		str_print(&line->val_cmd->cmd, output);
		for (size_t i = 0; i < line->val_cmd->args->len; ++i) {
			fprintf(output, " %ld", (long int) line->val_cmd->args->items[i]);
		}
		fputc('\n', output);
		// fputs(bval ? "true\n" : "false\n", output);
	}
	if (!error.any) {
		++*line_i;
	}
}
