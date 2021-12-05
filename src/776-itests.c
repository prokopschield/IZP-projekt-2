#include <string.h>

const char* reserved_words[] = { "true", "false", "empty", "card", "complement", "union", "intersect", "minus", "subseteq", "subset", "equals", "reflexive", "symmetric", "antisymmetric", "transitive", "function", "domain", "codomain", "injective", "surjective", "bijective", "closure_ref", "closure_sym", "closure_trans", "select" };

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
		for (size_t i = 0; i < 25; ++i) {
			if (!strcmp((char*) s.data, reserved_words[i])) {
				throw_chars("Element ");
				element_print(element, stderr);
				fprintf(stderr, " is a reserved word!\n");
			}
		}
	}
}
