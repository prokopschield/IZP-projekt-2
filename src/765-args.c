bool arg_A_val(arg_A_t* res, array_t* lines, size_t_array_t* args) {
	if (args->len < 1) {
		throw_chars("Insufficient arguments: ");
		return false;
	}
	line_t* arg_1 = lineload(lines, args->items[0]);
	res->A = arg_1->val_set ? arg_1->val_set : (set_t*) arg_1->val_rel;
	if (args->len >= 2) {
		res->N = args->items[1];
	}
	if (res->A) {
		return true;
	} else {
		invalid_argument(arg_1);
		return false;
	}
}
