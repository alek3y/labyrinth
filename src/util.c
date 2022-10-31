#include <stdio.h>
#include <string.h>
#include "term.h"
#include "util.h"

void print_clean(char *string) {
	unsigned int columns = term_width();

	char empty_line[columns + 1];
	memset(empty_line, ' ', columns);
	empty_line[columns] = 0;

	printf("\r%s\r%s", empty_line, string);
}
