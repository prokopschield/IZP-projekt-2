#include <stdbool.h>
#include <stdio.h>

bool cmd_bijective(rel_t* rel, set_t* set1, set_t* set2) {
	return (cmd_injective(rel, set1, set2) && cmd_surjective(rel, set1, set2));
}
