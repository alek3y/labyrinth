//! @file player.h
//! @brief Gestione del giocatore.

#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <stdbool.h>
#include "map.h"

//! @brief Struttura contenente le informazioni del giocatore.
typedef struct {
	char symbol;
	size_t x, y;
	long score;
} Player;

//! @brief Genera il giocatore e rimuove il simbolo corrispondente dalla mappa.
//! @return Il giocatore con posizione corrispondente a quella sulla mappa.
Player player_retrieve(Map map, char symbol);

//! @brief Controlla se può muoversi, lo sposta e aggiorna il suo punteggio.
//! @details Contiene le regole che aggiornano il punteggio in base ai simboli
//! definiti all'interno dello struct `Map`.
//! @param player Giocatore da spostare.
//! @param dx Differenza di colonne di cui spostarsi.
//! @param dy Differenza di righe di cui spostarsi.
//! @param map Mappa su cui si dovrebbe spostare il giocatore.
//! @return Vero, se è stato possibile spostare il giocatore, altrimenti falso.
bool player_step(Player *player, long dx, long dy, Map map);

#endif
