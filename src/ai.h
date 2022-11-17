//! @file ai.h
//! @brief Logica per l'AI del gioco.

#ifndef AI_H
#define AI_H

#include <stdio.h>
#include "map.h"
#include "player.h"

//! @brief Struttura contenente la lista di passaggi
//! fatti dall'AI per arrivare all'uscita.
typedef struct {
	size_t *steps;
	size_t length;
} Steps;

//! @brief Genera le mosse dell'AI partendo dalla posizione del giocatore..
//! @param source Stato iniziale del giocatore da cui partire.
//! @param map Mappa da attraversare.
//! @return La lista degli indici dei nodi che sono stati attraversati.
Steps ai_steps(Player source, Map map);

//! @brief Libera la memoria occupata dagli step dell'AI.
void ai_free(Steps *steps);

#endif
