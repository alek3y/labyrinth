//! @file map.h
//! @brief Gestione dei dati riguardante la mappa di gioco.

#ifndef MAP_H
#define MAP_H

#include <stdio.h>

//! @brief Struttura contenente le informazioni della mappa.
typedef struct {
	char *map;
	size_t rows, columns;
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

//! @brief Carica la mappa dal file `level`.
//! @details La lettura non parte dall'inizio del file,
//! ma dal punto in cui si trova il cursore.
//! @return La struttura generata dal contenuto del file.
Map map_load(FILE *level);

//! @brief Trova la cella sulla mappa.
//! @return Un puntatore alla cella della mappa nella
//! riga `y` e nella colonna `x`.
char *map_at(Map map, size_t x, size_t y);

//! @brief Libera la memoria occupata dalla mappa.
void map_free(Map *map);

#endif
