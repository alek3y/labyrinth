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
//! Se il giocatore dovesse passare per un **imprevisto** (rappresentato da `!`), gli
//! verranno dimezzati i punti moneta.

//! @file main.c
//! @brief Logica di gioco principale.

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "term.h"
#include "map.h"
#include "player.h"
#include "util.h"
#include "config.h"

//! @brief Entry del programma contenente il loop di gioco principale.
//! @return Valori non-zero se c'è stato un errore durante l'inizializzazione.
int main(void) {
	Map map = {
		.obstacle = SYMBOL_OBSTACLE,
		.coin = SYMBOL_COIN,
		.exit = SYMBOL_EXIT,
		.collisions = COLLISIONS
	};
	map_from_str(&map, DEFAULT_LEVEL);
	Player player = player_retrieve(map, SYMBOL_PLAYER);

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

			if (x + 1 >= map.columns) {

				// TODO: Se la mappa è troppo piccola non tutti i testi si vedono
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

	map_free(&map);
	return 0;
}
