#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <assert.h>
#include "player.h"
#include "ai.h"

long ai_find(Player source, Map map, long *path, long *best_path, long *best_score) {
	if (map.map[source.y * map.columns + source.x] == map.exit) {
		if (source.score > *best_score) {
			*best_score = source.score;
			memcpy(best_path, path, (map.rows * map.columns) * sizeof(*best_path));
		}

		return source.score;
	}

	long best = LONG_MIN;
	long best_dx = 0, best_dy = 0;
	long neighbors[][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
	for (size_t i = 0; i < 4; i++) {
		Player player = source;
		if (player_step(&player, neighbors[i][0], neighbors[i][1], map)) {
			long *cell = &path[player.y * map.columns + player.x];

			// Ignora le celle già visitate
			if (*cell > 0) {
				continue;
			}


			*cell = path[source.y * map.columns + source.x] + 1;	// Segna come visitata
			long score = ai_find(player, map, path, best_path, best_score);
			*cell = 0;

			if (score > best) {
				best = score;
				best_dx = neighbors[i][0];
				best_dy = neighbors[i][1];
			}
		}
	}

	if (best_dx == 0 && best_dy == 0) {
		return LONG_MIN;
	}

	return best;
}
