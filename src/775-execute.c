void execute(array_t* error, array_t* lines, size_t* line_i, FILE* output) {
	arr_push(error, NULL);
	arr_pop(error);
	line_t* line = lines->items[*line_i];
	fprintf(output, "%s\n", (char*) line->input.data);
	++*line_i;
}
