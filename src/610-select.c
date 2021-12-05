//
// Created by jiris on 04/12/2021.
//
#include <stdio.h>
#include <stdlib.h>

set_t* cmd_select(set_t* set) {
	set_t* newset = empty_set();
	add_element_to_set(set->elements[rand() % set->number_of_elements], &newset);
	return newset;
}
