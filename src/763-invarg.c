void invalid_argument(line_t* line) {
	throw_chars("Invalid argument: ");
	line_print(line, stderr);
}
