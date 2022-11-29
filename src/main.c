//! @mainpage Progetto
//!
//! ```plain
//! ###################
//! o    #          $ #
//! #    #          $ #
//! #    #   !  #   $ #
//! #    #      #   $ #
//! #    #      #     _
//! #    #      #     #
//! #           #     #
//! #    $$$$   #     #
//! ###################
//! ```
//!
//! Il **giocatore** (rappresentato da `o`) ha l'obiettivo di **trovare il miglior
//! percorso** per l'uscita (rappresentata dal simbolo `_`).
//!
//! Le **mosse** effettuabili dal giocatore sono:
//! - `N`, per andare verso _Nord_
//! - `E`, per andare verso _Est_
//! - `S`, per andare verso _Sud_
//! - `O`, per andare verso _Ovest_
//!
//! Il **miglior percorso** rappresenta la distanza percorsa minore dall'uscita
//! e i punti moneta accumulati (rappresentate da `$`) maggiori possibili.
//!
//! Se il giocatore dovesse passare per un **imprevisto** (rappresentato da `!`),
//! gli verranno dimezzati i punti moneta.

//! @file main.c
//! @brief Logica di gioco principale.

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "term.h"
#include "map.h"
#include "player.h"
#include "ai.h"
#include "util.h"
#include "config.h"

//! @brief Loop di gioco principale per la modalità interattiva.
void mode_interactive(Player player, Map map);

//! @brief Logica per l'elaborazione del percorso migliore.
void mode_ai(Player player, Map map);

//! @brief Entry del programma con l'inizializzazione della mappa.
int main(int argc, char **argv) {
	bool ai_mode = false;
	for (int i = 0; i < argc; i++) {
		if (strcmp(argv[i], "--challenge") == 0) {
			ai_mode = true;
		}
	}

	Map map = {
		.obstacle = OBSTACLE,
		.coin = COIN,
		.exit = EXIT,
		.collisions = COLLISIONS
	};

	Player player = {
		.symbol = PLAYER, .score = SCORE,
		.obstacle = OBSTACLE_LOSS,
		.step = STEP_LOSS,
		.coin = COIN_GAIN
	};

	if (!ai_mode) {
		map_from_str(&map, DEFAULT_LEVEL);
	} else {
		size_t columns, rows;
		scanf("%lu\n%lu\n", &columns, &rows);
		map_from_stdin(&map, columns, rows);
	}

	player_retrieve(&player, map);

	if (!ai_mode) {
		mode_interactive(player, map);
	} else {
		mode_ai(player, map);
	}

	map_free(&map);
	return 0;
}

void mode_ai(Player player, Map map) {

		// La lunghezza massima dei percorsi non ciclici è rows * columns
		bool *best_path = calloc(map.rows * map.columns, sizeof(*best_path));
		bool *path = calloc(map.rows * map.columns, sizeof(*path));

		// Evita di ricontrollare la posizione iniziale del giocatore
		size_t source = player.y * map.columns + player.x;
		path[source] = true;

		long best_score = LONG_MIN;	// Il migliore ha il punteggio più alto
		ai_find(player, map, path, best_path, &best_score);

		if (best_score > LONG_MIN) {
			printf("Score: %ld\n", best_score);	// DEBUG
		} else {
			fprintf(stderr, "Errore: impossibile trovare un percorso per l'uscita\n");
		}

		free(path);
		free(best_path);
}

void mode_interactive(Player player, Map map) {
	bool should_quit = false;
	while (true) {
		char map_row[map.columns + 1];	// TODO: Malloc?
		map_row[map.columns] = '\0';

		MAP_ITERATE(map, i, x, y) {
			if ((long) x == player.x && (long) y == player.y) {
				map_row[x] = player.symbol;
			} else {
				map_row[x] = map.map[i];
			}

			if (x + 1 >= map.columns) {
				if (y == 1) {
					printf_clean("%s  Score: %ld", map_row, player.score);
				} else {
					printf_clean("%s", map_row);
				}

				printf("\n");
			}
		}
		fflush(stdout);

		// Leggi la mossa da tastiera
		long dx = 0, dy = 0;
		while ((!should_quit) && (dx == 0 && dy == 0)) {
			char input = term_getch();
			if (input == KEY_QUIT || input == EOF) {
				should_quit = true;
				break;
			}

			switch (input) {
				case KEY_UP:
				case KEY_UP + 0x20:	// Versione minuscola
					dy = -1;
					break;
				case KEY_RIGHT:
				case KEY_RIGHT + 0x20:
					dx = 1;
					break;
				case KEY_DOWN:
				case KEY_DOWN + 0x20:
					dy = 1;
					break;
				case KEY_LEFT:
				case KEY_LEFT + 0x20:
					dx = -1;
					break;
			}
		}

		if (should_quit) {
			printf_clean("\r");
			printf("\n");
			break;
		}

		if (player_step(&player, dx, dy, map)) {
			char *cell = map_at(map, player.x, player.y);

			if (*cell == map.exit) {
				should_quit = true;
			} else {
				*cell = ' ';	// Rimuove l'oggetto raccolto
			}
		}

		term_cursor_move(-map.rows, 0);
	}
}
