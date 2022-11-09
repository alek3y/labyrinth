#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"
#include "player.h"

Player player_retrieve(Map map, char symbol) {
	Player player = {.symbol = symbol, .score = 0};

	MAP_ITERATE(map, i, x, y) {
		if (map.map[i] == symbol) {
			map.map[i] = ' ';
			player.x = x;
			player.y = y;
			break;
		}
	}

	return player;
}

bool player_step(Player *player, long dx, long dy, Map map, char *collisions) {

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
	if (strchr(collisions, *map_at(map, x, y)) != NULL) {
		return false;
	}

	player->x = x;
	player->y = y;
	return true;
}
