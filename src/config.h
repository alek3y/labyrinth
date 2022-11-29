//! @file config.h
//! @brief Configurazione di base del gioco.

#ifndef CONFIG_H
#define CONFIG_H

#define KEY_UP 'N'
#define KEY_RIGHT 'E'
#define KEY_DOWN 'S'
#define KEY_LEFT 'O'
#define KEY_QUIT 0x4

#define SCORE 1000
#define PLAYER 'o'
#define EXIT '_'

#define COLLISIONS ((char[]) {'#', '\0'})

#define ITEM_COIN_SYMBOL '$'
#define ITEM_OBSTACLE_SYMBOL '!'
#define ITEM_DRILL_SYMBOL 'T'

#define ITEM_COIN_VALUE 10
#define ITEM_OBSTACLE_VALUE 2
#define ITEM_DRILL_VALUE 3

#define DEFAULT_LEVEL \
	"###################\n" \
	"o    #          $ #\n" \
	"#    #          $ #\n" \
	"#    #   !  #   $ #\n" \
	"#    #      #   $ #\n" \
	"#    #      #     _\n" \
	"#    #      #     #\n" \
	"#           #     #\n" \
	"#    $$$$   #     #\n" \
	"###################\n"

#endif
