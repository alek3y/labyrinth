//! @file config.h
//! @brief Configurazione di base del gioco.

#ifndef CONFIG_H
#define CONFIG_H

#define KEY_UP 'N'
#define KEY_RIGHT 'E'
#define KEY_DOWN 'S'
#define KEY_LEFT 'O'
#define KEY_QUIT 0x4

#define SYMBOL_PLAYER 'o'
#define SYMBOL_OBSTACLE '!'
#define SYMBOL_COIN '$'
#define SYMBOL_EXIT '_'

#define COLLISIONS ((char[]) {'#', '\0'})

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
