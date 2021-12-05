#include <stdbool.h>
#include <stdio.h>

bool cmd_injective(rel_t* rel, set_t* set1, set_t* set2) {
	if (rel == empty_rel()) {
		return true;
	}
	if (!cmd_subseteq(cmd_domain(rel), set1)) {
		return false;
	}
	if (!cmd_subseteq(cmd_codomain(rel), set2)) {
		return false;
	}
	if (!cmd_function(rel)) {
		return false;
	}
	return (set1->number_of_elements == rel->number_of_pairs);
}
