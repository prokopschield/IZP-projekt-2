#include <stdbool.h>
#include <stdio.h>

typedef struct error_t {
	bool any;
	bool malloc;
} error_t;

error_t error = { false, false };

#define throw(e)(e = error.any = true)
#define throw_error(format, ...)																							 \
	((error.any = true), fprintf(stderr, "Error :: " format "\n", __VA_ARGS__))
#define throw_chars(txt) ((error.any = true), fprintf(stderr, "Error :: " txt))
