#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "map.h"
#include "player.h"

Tail tail_new() {
	return (Tail) {0};
}

Tail *tail_get(Tail tail, size_t index) {
	assert(index < tail.length);

	Tail *first = tail.next;
	for (size_t i = 0; i < index; i++) {
		first = first->next;
	}
	return first;
}

Tail *tail_find(Tail *tail, long x, long y, size_t *index) {
	assert(tail != NULL);

	size_t i = 0;
	Tail *next = tail, *found = NULL;
	while ((next = next->next) != NULL) {
		if (x == next->x && y == next->y) {
			found = next;
			break;
		}
		i++;
	}

	if (index != NULL && found != NULL) {
		*index = i;
	}
	return found;
}

void tail_insert(Tail *tail, size_t index, long x, long y) {
	assert(tail != NULL);
	assert(index <= tail->length);

	Tail *new = calloc(1, sizeof(*new));
	new->x = x;
	new->y = y;

	if (index == 0) {
		new->next = tail->next;
		tail->next = new;
	} else {
		Tail *previous = tail_get(*tail, index-1);
		new->next = previous->next;
		previous->next = new;
	}
	tail->length++;
}

void tail_cut(Tail *tail, size_t index) {
	assert(tail != NULL);
	assert(index < tail->length);

	if (index == 0) {
		tail_free(tail);
	} else {
		tail_free(tail_get(*tail, index-1));
		tail->length = index;
	}
}

void tail_free(Tail *tail) {
	assert(tail != NULL);

	Tail *previous, *next = tail->next;
	while (next != NULL) {
		previous = next;
		next = next->next;
		free(previous);
	}
	tail->next = NULL;
	tail->length = 0;
}

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
	char *cell = &map.map[y * map.columns + x];
	if (strchr(map.collisions, *cell) != NULL) {
		if (player->drillables == 0) {
			return false;
		} else {
			player->drillables--;	// Trapassa il muro
		}
	}

	if (*cell == map.coin) {
		player->score += player->coin;
		if (player->tail != NULL) {
			tail_insert(player->tail, 0, player->x, player->y);
		}
	} else if (player->tail != NULL) {

		// Sposta la coda di una cella
		if (player->tail->length > 0) {

			// FIXME: Ogni step chiama un malloc() e un free()
			tail_cut(player->tail, player->tail->length-1);
			tail_insert(player->tail, 0, player->x, player->y);
		}

		// Taglia la coda se il player ci collide
		size_t index;
		if (tail_find(player->tail, x, y, &index) != NULL) {
			player->score -= player->coin * (player->tail->length - index);
			tail_cut(player->tail, index);
		}
	}

	if (*cell == map.drill) {
		player->drillables += player->drill;
	} else if (*cell == map.obstacle) {
		if (player->score < 0) {
			player->score *= player->obstacle;
		} else {
			player->score /= player->obstacle;
		}

		// Taglia a metà la coda nell'imprevisto
		if (player->tail != NULL) {
			tail_cut(player->tail, player->tail->length/2);
		}
	}

	player->score--;
	player->x = x;
	player->y = y;
	return true;
}
