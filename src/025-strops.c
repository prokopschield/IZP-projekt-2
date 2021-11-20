#include <stdbool.h>
#include <stdio.h>

void strop_skip_ws(string_t* restrict str, int* index) {
	register byte_t c;
	register const int len = (int) str->len;
	while ((c = str->data[*index]),
				 (c == ' ' || c == '\t' || c == '\r' || c == '\n')) {
		if (++(*index) >= len) {
			*index = EOF;
			return;
		}
	}
}

string_t strop_read_word(string_t* restrict str, int* index) {
	strop_skip_ws(str, index);
	int i = *index;
	int l = 0;
	while (str->data[i + l] > ' ') {
		++l;
	}
	string_t substr = str_alloc(l);
	for (int j = 0; j < l; ++j) {
		substr.data[j] = str->data[(*index)++];
	}
	strop_skip_ws(str, index);
	return substr;
}

bool str_equal(string_t* left, string_t* right) {
	if (left == right)
		return true;
	if (left->len != right->len)
		return false;
	for (size_t i = 0, l = right->len; i < l; ++i) {
		if (left->data[i] != right->data[i]) {
			return false;
		}
	}
	return true;
}

void str_print(string_t* str, FILE* stream) {
	for (size_t i = 0; i < str->len; ++i) {
		putc(str->data[i], stream);
	}
}
