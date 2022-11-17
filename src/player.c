#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "map.h"
#include "player.h"

void player_retrieve(Player *player, Map map) {
	MAP_ITERATE(map, i, x, y) {
		if (map.map[i] == player->symbol) {
			map.map[i] = ' ';
			player->x = x;
			player->y = y;
			break;
		}
	}
}

//! @details La funzione contiene le regole che aggiornano il punteggio del
//! giocatore in base ai simboli definiti all'interno dello struct `Map`.
bool player_step(Player *player, long dx, long dy, Map map) {
	assert(player != NULL);

	// Confine Nord-Ovest
	if ((dx < 0 && (size_t) labs(dx) > player->x) || (dy < 0 && (size_t) labs(dy) > player->y)) {
		return false;
	}

	size_t x = player->x + dx, y = player->y + dy;

	// Confine Sud-Est
	if (x >= map.columns || y >= map.rows) {
		return false;
	}

	// Collisioni in base al contenuto della cella
	if (strchr(map.collisions, *map_at(map, x, y)) != NULL) {
		return false;
	}

	player->x = x;
	player->y = y;

	// Aggiorna lo score del giocatore in base al contenuto della mappa
	char *cell = map_at(map, x, y);
	if (*cell == map.obstacle) {
		if (player->score < 0) {
			player->score *= player->obstacle_loss;
		} else {
			player->score /= player->obstacle_loss;
		}
	} else if (*cell == map.coin) {
		player->score += player->coin_gain;
	} else if (*cell == ' ') {
		player->score -= player->step_loss;
	}

	return true;
}
