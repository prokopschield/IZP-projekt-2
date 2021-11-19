#include <stdio.h>

int main() {


    element_t e = { 1, NULL };
    element_t* pole[] = { &e };
    set_t set1 = { 0, 1, &pole };



//    printf("%s", set1.elements[0]->str.data);

    if(Command_empty(&set1))
        puts("true");
    else
        puts("false");

    Command_card(&set1);

	// Remember to free everything!!!
	mem_free_everything();
}
