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
#include "map.h"

//! @brief Entry del programma contenente il loop di gioco principale.
//! @return Valori non-zero se c'è stato un errore durante l'inizializzazione.
int main(void) {
	FILE *level = fopen("res/levels/0.txt", "r");
	Map map = map_load(level);
	fclose(level);

	for (size_t y = 0; y < map.rows; y++) {
		printf("|");
		for (size_t x = 0; x < map.columns; x++) {
			printf("%c", *map_at(map, y, x));
		}
		printf("|\n");
	}

	printf("%lu %lu\n", map.rows, map.columns);

	map_free(&map);
}
