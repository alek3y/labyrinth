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
#include "util.h"
#include "map.h"
#include "player.h"
#include "config.h"

//! @brief Entry del programma contenente il loop di gioco principale.
//! @return Valori non-zero se c'è stato un errore durante l'inizializzazione.
int main(void) {
	FILE *level = fopen(PATH_LEVELS "/0.txt", "r");	// TODO: Supporto per più livelli
	if (level == NULL) {
		return 1;
	}

	Map map = map_load(level);
	Player player = player_retrieve(SYMBOL_PLAYER, map);

	while (true) {
		printf("\r");
		map_print(map);
		msleep(1000);
		cursor_move_rows(-map.rows);
	}

	map_free(&map);
	fclose(level);
}
