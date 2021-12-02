array_t* all_pairs() {
	static array_t* all_pairs = NULL;
	if (!all_pairs) {
		all_pairs = arr_alloc(1);
		if (!all_pairs) {
			throw(error.malloc);
			return NULL;
		}
		arr_push(all_pairs, NULL); // start numbering at 1
	}
	return all_pairs;
}

pair_t* get_pair(element_t* left, element_t* right) {
	array_t* pairs = all_pairs();
	if (!pairs) {
		throw(error.malloc);
		return NULL;
	}
	for (size_t i = 1; i < pairs->len; ++i) {
		pair_t* p = (pair_t*) pairs->items[i];
		if (p->left == left && p->right == right) {
			return p;
		}
	}
	pair_t* p = (pair_t*) buffer_alloc(sizeof(pair_t));
	if (!p) {
		throw(error.malloc);
		return NULL;
	}
	p->left = left;
	p->right = right;
	arr_push(pairs, p);
	return p;
}

void pair_print(pair_t* pair, FILE* stream) {
	putc('(', stream);
	element_print(pair->left, stream);
	putc(' ', stream);
	element_print(pair->right, stream);
	putc(')', stream);
}
