set_t* get_universe(array_t* lines) {
	line_t* universe_line = lines->items[1];
	if (!universe_line) {
		return empty_set();
	}
	set_t* universe = universe_line->val_set;
	if (!universe) {
		return empty_set();
	}
	const array_t* elements = all_elements();
	if (universe->number_of_elements != elements->len) {
		for (size_t i = 0; i < elements->len; ++i) {
			add_element_to_set(elements->items[i], &universe);
		}
		universe_line->val_set = universe;
	}
	return universe;
}
