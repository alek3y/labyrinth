#include <stdio.h>
#include "map.h"
#include "player.h"

Player player_retrieve(char symbol, Map map) {
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
