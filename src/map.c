#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include "map.h"

Map map_load(FILE *level) {
	assert(level != NULL);

	Map map = {.rows = 0, .columns = 0};
	long start = ftell(level);

	size_t columns = 0;
	while (true) {
		char cell = fgetc(level);
		if (cell == '\n' || cell == EOF) {
			if (columns == 0) {
				break;	// Ferma il parsing a "\n\n" o {'\n', EOF}
			}

			if (columns > map.columns) {
				map.columns = columns;
			}
			columns = 0;

			map.rows++;
		} else {
			columns++;
		}
	}

	fseek(level, start, SEEK_SET);
	map.map = malloc(map.rows * map.columns);
	for (size_t i = 0; i < map.rows * map.columns; ) {
		char cell = fgetc(level);
		if (cell == '\n' || cell == EOF) {

			// Riempi le colonne mancanti con spazi
			if (i % map.columns != 0) {
				size_t padding = map.columns - (i % map.columns);
				memset(&map.map[i], ' ', padding);
				i += padding;
			}
		} else {
			map.map[i++] = cell;
		}
	}

	fseek(level, 2, SEEK_CUR);	// Salta il "\n\n" se presente
	return map;
}

char *map_at(Map map, size_t x, size_t y) {
	assert(x < map.columns);
	assert(y < map.rows);

	return &map.map[y * map.columns + x];
}

void map_free(Map *map) {
	assert(map->map != NULL);

	free(map->map);
	memset(map, 0, sizeof(*map));
}
