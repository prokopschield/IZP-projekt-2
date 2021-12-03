string_t read_word(FILE* stream, bool* EOL) {
	static int length = 0;
	static char buffer[READ_BUFFER_LENGTH] = { 0 };
	do {
		while ((buffer[length++] = getc(stream)) > ' ') {
			if (length > MAX_ELEMENT_LENGTH) {
				throw_error("Element %s is longer than %d chars.", buffer, MAX_ELEMENT_LENGTH);
				break;
			}
		}
		if (buffer[--length] == '\n')
			*EOL = true;
		buffer[length] = 0; // null-terminate string
	} while (!length && !feof(stream));
	string_t str = str_alloc(length);
	if (!str.len) {
		throw_error("Could not read word '%s'", buffer);
		return str;
	}
	for (int i = 0; i <= length; ++i) {
		str.data[i] = buffer[i];
	}
	length = 0;
	while ((buffer[length++] = getc(stream)) <= ' ') {
		if (buffer[--length] == EOF) {
			*EOL = true;
			break;
		} else if (buffer[length] == '\n') {
			*EOL = true;
		}
	}
	return str;
}
