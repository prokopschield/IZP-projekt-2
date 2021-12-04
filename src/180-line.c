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

void line_print(line_t* line, FILE* stream) {
	if (!line) {
		putc('\n', stream);
	} else if (line->val_rel) {
		rel_print(line->val_rel, stream, 0);
	} else if (line->val_set) {
		set_print(line->val_set, stream, line->line == 1);
	} else if (line->val_cmd) {
		fputs("C ", stream);
		str_print(&line->val_cmd->cmd, stream);
		size_t_array_t* args = (size_t_array_t*) line->val_cmd->args;
		for (size_t i = 0; i < args->len; ++i) {
			fprintf(stream, " %ld", args->items[i]);
		}
		fputc('\n', stream);
	} else {
		putc('\n', stream);
	}
}
