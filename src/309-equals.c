#include <stdbool.h>
#include <stdio.h>

bool cmd_equals(set_t* set_A, set_t* set_B) {
	if (set_A == set_B)
		return true;
	else
		return false;
}
