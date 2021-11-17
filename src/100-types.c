#include <stdbool.h>

typedef struct element_t {
	size_t uid;
	string_t str;
} element_t;

typedef struct set_t {
	size_t line;
	size_t number_of_elements;
	element_t** elements;
} set_t;

typedef struct pair_t {
	element_t* left;
	element_t* right;
} pair_t;

typedef struct rel_t {
	size_t line;
	size_t number_of_pairs;
	pair_t** pairs;
} rel_t;

enum line_type_t {
	line_type_undefined,
	line_type_set,
	line_type_rel,
	line_type_bool
} line_type_t;

typedef struct line_t {
	size_t line;
	byte_t line_type;
	set_t* val_set;
	rel_t* val_rel;
	bool val_bool;
	string_t input;
} line_t;
