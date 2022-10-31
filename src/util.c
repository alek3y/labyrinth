#include <stdio.h>
#include <string.h>
#include "term.h"
#include "util.h"

void print_clean(char *string) {
	printf("\r%s", string);

	unsigned int columns = term_width() - 1;
	size_t string_len = strlen(string);
	if (string_len <= columns) {
		size_t empty_len = columns - string_len;

		char empty[empty_len + 1];
		memset(empty, ' ', empty_len);
		empty[empty_len] = 0;

		printf("%s", empty);
		term_cursor_move(0, -empty_len);
	}
}
