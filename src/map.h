//! @file map.h
//! @brief Gestione dei dati riguardante la mappa di gioco.

//! @brief Struttura contenente le informazioni della mappa.
typedef struct {
	char *map;
	size_t rows, columns;
} Map;

//! @brief Carica la mappa dal file `level`.
//! @details La lettura non parte dall'inizio del file,
//! ma dal punto in cui si trova il cursore.
//! @return La struttura generata dal contenuto del file.
Map map_load(FILE *level);

//! @brief Trova la cella sulla mappa.
//! @return Un puntatore alla cella della mappa nella
//! riga `row` e nella colonna `column`.
char *map_at(Map map, size_t row, size_t column);

//! @brief Libera la memoria occupata dalla mappa.
void map_free(Map *map);
