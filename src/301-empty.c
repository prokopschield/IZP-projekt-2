#include <stdbool.h>
#include <stdio.h>

// returns true if empty, false if not empty
bool cmd_empty(set_t* set) {
    if (set->number_of_elements == 0)
        return true;
    return false;
}