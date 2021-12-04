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

typedef struct cmd_t {
	string_t cmd;
	array_t* args;
} cmd_t;

enum line_type_t {
	line_type_undefined, line_type_set, line_type_rel, line_type_cmd,
};

typedef struct line_t {
	size_t line;
	byte_t line_type;
	set_t* val_set;
	rel_t* val_rel;
	cmd_t* val_cmd;
} line_t;
