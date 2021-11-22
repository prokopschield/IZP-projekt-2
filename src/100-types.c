#include <stdbool.h>

typedef struct checksum_t {
	size_t product;
	size_t sum;
} checksum_t;

typedef struct element_t {
	size_t uid;
	string_t str;
} element_t;

typedef struct set_t {
	checksum_t checksum;
	size_t line;
	size_t number_of_elements;
	element_t** elements;
} set_t;

typedef struct pair_t {
	checksum_t checksum;
	element_t* left;
	element_t* right;
} pair_t;

typedef struct rel_t {
	checksum_t checksum;
	size_t line;
	size_t number_of_pairs;
	pair_t** pairs;
} rel_t;

enum cmd_type_t {
	cmd_empty = 0x01,
	cmd_card,
	cmd_complement,
	cmd_union,
	cmd_intersect,
	cmd_minus,
	cmd_subseteq,
	cmd_subset,
	cmd_equals,
	cmd_reflexive = 0x21,
	cmd_symmetric,
	cmd_antisymmetric,
	cmd_transitive,
	cmd_function,
	cmd_domain,
	cmd_codomain,
	cmd_injective,
	cmd_surjective,
	cmd_bijective,
	cmd_closure_ref = 0x41,
	cmd_closure_sym,
	cmd_closure_trans,
	cmd_select = 0x61,
};

typedef struct cmd_t {
	set_t* A;
	set_t* B;
	rel_t* R;
	size_t N;
	byte_t cmd_type;
} cmd_t;

enum line_type_t {
	line_type_undefined,
	line_type_set,
	line_type_rel,
	line_type_cmd,
	line_type_bool
};

typedef struct line_t {
	size_t line;
	byte_t line_type;
	set_t* val_set;
	rel_t* val_rel;
	cmd_t* val_cmd;
} line_t;
