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
#define SYMBOL_WALL '#'
#define SYMBOL_OBSTACLE '!'
#define SYMBOL_COIN '$'
#define SYMBOL_EXIT '_'

#define COLLISIONS ((char[]) {SYMBOL_WALL, '\0'})

#define PATH_LEVELS "res/levels"

#endif
