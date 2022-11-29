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

	long x = player->x + dx, y = player->y + dy;

	// Confine Nord-Ovest
	if (x < 0 || y < 0) {
		return false;
	}

	// Confine Sud-Est
	if (x >= (long) map.columns || y >= (long) map.rows) {
		return false;
	}

	// Collisioni in base al contenuto della cella
	char *cell = map_at(map, x, y);
	if (strchr(map.collisions, *cell) != NULL) {
		return false;
	}

	// Aggiorna lo score del giocatore in base al contenuto della mappa
	if (*cell == map.obstacle) {
		if (player->score < 0) {
			player->score *= player->obstacle;
		} else {
			player->score /= player->obstacle;
		}
	} else if (*cell == map.coin) {
		player->score += player->coin;
	} else if (*cell == ' ') {
		player->score -= player->step;
	}

	player->x = x;
	player->y = y;
	return true;
}
