bool arg_A_val(arg_A_t* res, array_t* lines, size_t_array_t* args) {
	if (args->len < 1) {
		throw_error("Insufficient (%ld) arguments for empty()", args->len);
		return false;
	}
	line_t* arg_1 = line_get(lines, args->items[0]);
	if (!arg_1) {
		arg_1 = line_get(lines, 0);
	}
	eval(lines, arg_1);
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
