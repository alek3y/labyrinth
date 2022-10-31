//! @file player.h
//! @brief Gestione del giocatore.

#ifndef PLAYER_H
#define PLAYER_H

#include <stdbool.h>
#include "map.h"

//! @brief Struttura contenente le informazioni del giocatore.
typedef struct {
	char symbol;
	size_t x, y;
	long score;
} Player;

//! @brief Genera e rimuove il simbolo corrispondente al giocatore dalla mappa.
//! @return Il giocatore con posizione corrispondente a quella sulla mappa.
Player player_retrieve(Map map, char symbol);

//! @brief Controlla se il giocatore può muoversi e lo sposta sulla mappa.
//! @param map Mappa su cui si dovrebbe spostare.
//! @param player Giocatore su cui va effettuato lo spostamento.
//! @param dx Differenza di colonne di cui spostarsi.
//! @param dy Differenza di righe di cui spostarsi.
//! @return Vero, se è stato possibile spostare il giocatore, altrimenti falso.
bool player_step(Player *player, long dx, long dy, Map map);

#endif
