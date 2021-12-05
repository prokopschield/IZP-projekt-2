#include <stdbool.h>
#include <stdio.h>

// checks whether set_A is subseteq of set_B and
// if number of elements in set_A is lower than in set_B return true, else
// returns false
bool cmd_subset(set_t* set_A, set_t* set_B) {
	if (cmd_subseteq(set_A, set_B) && set_A->number_of_elements < set_B->number_of_elements) {
		return true;
	} else {
		return false;
	}
}
