//! @file player.h
//! @brief Gestione del giocatore.

#ifndef PLAYER_H
#define PLAYER_H

#include "map.h"

//! @brief Struttura contenente le informazioni del giocatore.
typedef struct {
	char symbol;
	size_t x, y;
	long score;
} Player;

//! @brief Genera e rimuove il simbolo corrispondente al giocatore dalla mappa.
//! @return Il giocatore con posizione corrispondente a quella sulla mappa.
Player player_retrieve(char symbol, Map map);

#endif
