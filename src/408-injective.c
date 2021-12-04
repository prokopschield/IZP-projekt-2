#include <stdbool.h>
#include <stdio.h>

bool cmd_injective(rel_t *rel,set_t *set1,set_t *set2){
    set_t* setright = empty_set();
    set_t* setleft = empty_set();
    for (size_t i = 0; i < rel->number_of_pairs; i++) {
        if(!is_element_in_set(rel->pairs[i]->right, setright) && is_element_in_set(rel->pairs[i]->right, set2)){
            add_element_to_set(rel->pairs[i]->right, &setright);
        } 
        else {
            return false;    
        }
        if(!is_element_in_set(rel->pairs[i]->left, setleft) && is_element_in_set(rel->pairs[i]->right, set1)){
            add_element_to_set(rel->pairs[i]->left, &setleft);
        }
        else {
            return false;    
        }
    }  
    
    if (set1->number_of_elements != setleft->number_of_elements ){
        return false;
    }
  
    return true;
}
