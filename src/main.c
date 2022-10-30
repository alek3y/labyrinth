
#include <stdio.h>
#include "map.h"

int main(void) {
	FILE *level = fopen("res/levels/0.txt", "r");
	Map map = map_load(level);
	fclose(level);

	for (size_t y = 0; y < map.rows; y++) {
		printf("|");
		for (size_t x = 0; x < map.columns; x++) {
			printf("%c", *map_at(map, y, x));
		}
		printf("|\n");
	}

	printf("%lu %lu\n", map.rows, map.columns);

	map_free(&map);
}
