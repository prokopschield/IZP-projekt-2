void input_tests() {
	// only letters allowed!
	array_t* elements = all_elements();
	for (size_t i = 1; i < elements->len; ++i) {
		element_t* element = ((element_t*) elements->items[i]);
		string_t s = element->str;
		for (size_t i = 0; i < s.len; ++i) {
			if ((s.data[i] < 'A' || s.data[i] > 'Z') &&
					(s.data[i] < 'a' || s.data[i] > 'z')) {
				throw_chars("Invalid symbol in element: ");
				element_print(element, stderr);
				fputc('\n', stderr);
			}
		}
	}
}
