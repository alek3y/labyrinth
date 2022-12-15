//! @file player.h
//! @brief Gestione del giocatore.

#ifndef PLAYER_H
#define PLAYER_H

#include <stdbool.h>
#include "map.h"

//! @brief Lista dinamica che rappresenta la coda del giocatore.
typedef struct Tail {
	long x, y;
	size_t length;
	struct Tail *next;
} Tail;

//! @brief Inizializza la struttura vuota.
Tail tail_new();

//! @brief Restituisce il nodo all'indice `index`.
Tail *tail_get(Tail tail, size_t index);

//! @brief Cerca il nodo contenente i valori `x` e `y` e ne
//! salva l'indice su `index`.
Tail *tail_find(Tail *tail, long x, long y, size_t *index);

//! @brief Inizializza un nuovo nodo in posizione `index`
//! contenente i dati `x` e `y`.
void tail_insert(Tail *tail, size_t index, long x, long y);

//! @brief Taglia e libera la memoria occupata dalla coda
//! partendo dall'indice `index`.
void tail_cut(Tail *tail, size_t index);

//! @brief Libera dalla memoria l'intera coda.
void tail_free(Tail *tail);

//! @brief Struttura contenente le informazioni del giocatore
//! e i valori associati al cambio punti durante lo step.
typedef struct {
	char symbol;
	long x, y, score;
	long obstacle, coin, drill;
	size_t drillables;
	Tail *tail;
} Player;

//! @brief Genera il giocatore e rimuove il simbolo corrispondente dalla mappa.
//! @return Il giocatore con posizione corrispondente a quella sulla mappa.
void player_retrieve(Player *player, Map map);

//! @brief Controlla se può muoversi, lo sposta e aggiorna il suo punteggio.
//! @param player Giocatore da spostare.
//! @param dx Differenza di colonne di cui spostarsi.
//! @param dy Differenza di righe di cui spostarsi.
//! @param map Mappa su cui si dovrebbe spostare il giocatore.
//! @return Vero, se è stato possibile spostare il giocatore, altrimenti falso.
bool player_step(Player *player, long dx, long dy, Map map);

#endif
