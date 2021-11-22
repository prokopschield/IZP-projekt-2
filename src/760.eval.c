extern bool eval(array_t* error, set_t* universe, line_t* line);
bool eval(array_t* error, set_t* universe, line_t* line) {
	arr_push(error, universe);
	arr_push(error, line);
	return false;
}
