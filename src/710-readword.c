string_t read_word(FILE* stream, bool* EOL) {
	static int length = 0;
	static char buffer[READ_BUFFER_LENGTH] = { 0 };
	do {
		while ((buffer[length++] = getc(stream)) > ' ');
		if (buffer[--length] == '\n')
			*EOL = true;
		buffer[length] = 0; // null-terminate string
	} while (!length && !feof(stream));
	string_t str = str_alloc(length);
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
