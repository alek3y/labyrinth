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
#define OBSTACLE_LOSS 2
#define STEP_LOSS 1
#define COIN_GAIN 10

#define PLAYER 'o'
#define OBSTACLE '!'
#define COIN '$'
#define EXIT '_'

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
