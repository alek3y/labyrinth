//! @file map.h
//! @brief Gestione dei dati riguardante la mappa di gioco.

#ifndef MAP_H
#define MAP_H

#include <stdio.h>

//! @brief Struttura contenente le informazioni della mappa.
typedef struct {
	char *map;
	size_t rows, columns;
	char obstacle, coin, drill, exit;
	char *collisions;
} Map;

//! @brief Espande in un for loop per iterare le celle della mappa.
//! @param map Mappa da iterare.
//! @param i Indice progressivo della cella.
//! @param x Indice della colonna assegnata ad ogni iterazione.
//! @param y Indice della riga assegnata ad ogni iterazione.
#define MAP_ITERATE(map, i, x, y) \
	for ( \
		size_t i = 0, x = 0, y = 0; \
		i < (map).rows * (map).columns; \
		i++, x = i % (map).columns, y = i / (map).columns \
	)

//! @brief Carica la mappa dal file `level` sulla struttura `map`.
void map_from_file(Map *map, FILE *level);

//! @brief Carica la mappa dalla stringa `level` sulla struttura `map`.
void map_from_str(Map *map, char *level);

//! @brief Carica la mappa dallo _standard input_ sulla struttura `map`.
void map_from_stdin(Map *map, size_t columns, size_t rows);

//! @brief Trova la cella sulla mappa.
//! @return Un puntatore alla cella della mappa nella
//! riga `y` e nella colonna `x`.
char *map_at(Map map, size_t x, size_t y);

//! @brief Libera la memoria occupata dalla mappa.
void map_free(Map *map);

#endif
