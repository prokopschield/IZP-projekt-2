line_t* lineload(array_t* lines, size_t n) {
	line_t* line = line_get(lines, n);
	if (!line) {
		line = line_get(lines, 0);
	}
	eval(lines, line);
	return line;
}
