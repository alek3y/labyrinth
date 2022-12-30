#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include "map.h"

//! @details Perché la lettura funzioni, deve essere presente un
//! '\\n' su ogni riga della mappa (inclusa l'ultima).
void map_from_str(Map *map, char *level) {
	assert(map != NULL && level != NULL);

	map->columns = 0;
	char *head = level, *tail;
	while ((tail = strchr(head, '\n')) != NULL) {
		if ((size_t) (tail - head) > map->columns) {
			map->columns = tail - head;
		}

		head = tail + 1;
		map->rows++;
	}

	map->map = calloc(map->rows * map->columns + 1, 1);
	head = level;
	while ((tail = strchr(head, '\n')) != NULL) {
		size_t row_len = tail - head;
		strncat(map->map, head, row_len);

		// Riempi le colonne mancanti con spazi
		if (row_len < map->columns) {
			memset(map->map + strlen(map->map), ' ', map->columns - row_len);
		}

		head = tail + 1;
	}
}

//! @details La funzione comincia la lettura del file dal punto
//! in cui si trova il cursore e non dall'inizio del file.
//! Utilizza lo stesso standard di lettura di `map_from_str`.
void map_from_file(Map *map, FILE *level) {
	assert(map != NULL && level != NULL);

	long start = ftell(level);

	size_t buffer_len = 0, newlines = 0;
	while (true) {
		char cell = fgetc(level);
		if (cell == '\n') {
			newlines++;
		}

		if (newlines >= 2 || cell == EOF) {
			break;
		}

		newlines = 0;
		buffer_len++;
	}

	char *buffer = malloc(buffer_len);
	fseek(level, start, SEEK_SET);
	fread(buffer, 1, buffer_len, level);
	buffer[buffer_len] = '\0';

	map_from_str(map, buffer);

	free(buffer);
	fseek(level, 1, SEEK_CUR);	// Salta il "\n\n" se presente
}

//! @details Questa versione non permette la lettura di righe
//! con un numero di colonne diverso da `columns`.
void map_from_stdin(Map *map, size_t columns, size_t rows) {
	assert(map != NULL);

	map->rows = rows;
	map->columns = columns;

	map->map = malloc(rows * columns);
	for (size_t i = 0; i < rows; i++) {
		fread(map->map + i * columns, 1, columns, stdin);
		fgetc(stdin);	// Salta il '\n'
	}
}

char *map_at(Map map, size_t x, size_t y) {
	assert(map.map != NULL);
	assert(x < map.columns && y < map.rows);

	return &map.map[y * map.columns + x];
}

void map_free(Map *map) {
	assert(map->map != NULL);

	free(map->map);
	memset(map, 0, sizeof(*map));
}
