#include <stdbool.h>
#include <stdio.h>

bool cmd_surjective(rel_t* rel, set_t* set1, set_t* set2) {
	if (rel == empty_rel()) {
		return true;
	}
	if (!cmd_subseteq(cmd_domain(rel), set1)) {
		return false;
	}
	if (!cmd_function(rel)) {
		return false;
	}
	return (cmd_codomain(rel) == set2);
}
