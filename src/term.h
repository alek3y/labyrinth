//! @file term.h
//! @brief Funzioni per la manipolazione del terminale.

#ifndef TERM_H
#define TERM_H

//! @brief Sposta il cursore `dy` righe e `dx` colonne.
void term_cursor_move(int dy, int dx);

//! @brief Attende `ms` millisecondi.
void term_sleep(unsigned int ms);

//! @brief Legge la larghezza del terminale.
unsigned int term_width(void);

//! @brief Legge un carattere senza aspettare il tasto Invio.
char term_getch(void);

#endif
