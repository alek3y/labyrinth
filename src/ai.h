//! @file ai.h
//! @brief Logica per l'AI del gioco.

#ifndef AI_H
#define AI_H

#include "map.h"
#include "player.h"

//! @brief Trova il percorso migliore dal giocatore all'uscita
//! @param player Giocatore da cui cominciare la ricerca
//! @param map Mappa su cui effettuare la ricerca
//! @param path Buffer ausiliare lungo `map.rows * map.columns` per i nodi visitati
//! @param best_path Buffer ausiliare su cui ci sono i nodi visitati del percorso migliore
//! @param best_score Score percorso migliore (inizialmente `LONG_MIN`)
long ai_find(Player player, Map map, bool *path, bool *best_path, long *best_score);

#endif
