//
// Created by Štefan Pekník on 19.11.2021.
//

#include <stdbool.h>
#include <stdio.h>

bool cmd_subset (set_t *set1, set_t *set2) {
    if (set1 == set2)
        return false;
    else if (cmd_subseteq(set1, set2))
        return true;
    else
        return false;
}