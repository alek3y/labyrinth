#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <assert.h>
#include "player.h"
#include "ai.h"

// TODO:
// - Diminuire il peso sullo stack usando puntatori per Player e Map?
// - Ottimizzare (?) facendo una BFS su ogni nodo per evitare le ricerche dentro i vicoli ciechi
long ai_find(Player source, Map map, bool *path, bool *best_path, long *best_score) {
	if (*map_at(map, source.x, source.y) == map.exit) {
		if (source.score > *best_score) {
			*best_score = source.score;
			memcpy(best_path, path, (map.rows * map.columns) * sizeof(*best_path));
		}

		return source.score;
	}

	long best = LONG_MIN;
	long best_delta[2] = {0, 0};
	long neighbors[][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
	for (size_t i = 0; i < 4; i++) {
		Player player = source;
		if (player_step(&player, neighbors[i][0], neighbors[i][1], map)) {
			bool *cell = &path[player.y * map.columns + player.x];

			// Ignora le celle già visitate
			if (*cell) {
				continue;
			}

			*cell = true;	// Segna come visitata in modo da non tornare indietro
			long score = ai_find(player, map, path, best_path, best_score);
			*cell = false;

			if (score > best) {
				best = score;
				memcpy(best_delta, neighbors[i], sizeof(best_delta));
			}
		}
	}

	if (best_delta[0] == 0 && best_delta[1] == 0) {
		return LONG_MIN;
	}

	return best;
}
