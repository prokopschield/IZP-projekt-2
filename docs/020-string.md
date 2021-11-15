## strings

```C
struct string_t {
	mem_t* mem;
	size_t len;
	byte_t* data;
}
```

`string_t str_alloc(size_t size)` - allocate string, get struct

`string_t* str_palloc(size_t size)` - allocate string, get pointer

`str_free(string_t* str)` - de-allocate string

`string_t str_readline(FILE* stream)` - read line from stream - incompatible with stdin, must support fgetpos/fsetpos!
