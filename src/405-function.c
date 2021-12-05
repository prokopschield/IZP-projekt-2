#include <stdbool.h>

bool cmd_function(rel_t* rel) {
	set_t* domain = empty_set();
	for (size_t i = 0; i < rel->number_of_pairs; ++i) {
		if (is_element_in_set(rel->pairs[i]->left, domain)) {
			return false;
		} else {
			add_element_to_set(rel->pairs[i]->left, &domain);
		}
	}
	return true;
}
