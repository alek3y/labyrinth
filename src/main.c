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
		.obstacle_loss = OBSTACLE_LOSS,
		.step_loss = STEP_LOSS,
		.coin_gain = COIN_GAIN
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
	Steps steps = ai_steps(player, map);

	char *moves = malloc(steps.length + 1);
	moves[steps.length] = '\0';

	for (size_t i = 1; i < steps.length; i++) {
		size_t previous = steps.steps[i-1], current = steps.steps[i];

		if (current == previous - map.columns) {
			moves[i-1] = KEY_UP;
		} else if (current == previous + map.columns) {
			moves[i-1] = KEY_DOWN;
		} else if (current == previous - 1) {
			moves[i-1] = KEY_LEFT;
		} else if (current == previous + 1) {
			moves[i-1] = KEY_RIGHT;
		}
	}

	printf("%s\n", moves);

	free(moves);
	ai_free(&steps);
}

void mode_interactive(Player player, Map map) {
	bool should_quit = false;
	while (true) {
		char map_row[map.columns + 1];	// TODO: Malloc?
		map_row[map.columns] = '\0';

		MAP_ITERATE(map, i, x, y) {
			if (x == player.x && y == player.y) {
				map_row[x] = player.symbol;
			} else {
				map_row[x] = map.map[i];
			}

			// TODO: Se la mappa è troppo piccola non tutti i testi si vedono
			if (x + 1 >= map.columns) {
				switch (y) {
					case 1:
						printf_clean("%s   Score: %ld", map_row, player.score);
						break;
					case 3:
						printf_clean("%s   Controlli:", map_row);
						break;
					case 5:

						// TODO: La freccia non è supportata su cmd.exe
						printf_clean("%s         %c (↑)", map_row, KEY_UP);
						break;
					case 6:
						printf_clean("%s   %c (←) %c (↓) %c (→)", map_row, KEY_LEFT, KEY_DOWN, KEY_RIGHT);
						break;
					default:
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
