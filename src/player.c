#include <stdio.h>
#include <stdlib.h>
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

bool player_step(Player *player, long dx, long dy, Map map) {

	// Confine Nord-Ovest
	if ((dx < 0 && (size_t) labs(dx) > player->x) || (dy < 0 && (size_t) labs(dy) > player->y)) {
		return false;
	}

	// Confine Sud-Est
	if (player->x + dx >= map.columns || player->y + dy >= map.rows) {
		return false;
	}

	player->x += dx;
	player->y += dy;
	return true;
}
