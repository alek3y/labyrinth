//! @file term.h
//! @brief Funzioni per la manipolazione del terminale.

#ifndef TERM_H
#define TERM_H

//! @brief Sposta il cursore `dy` colonne.
//! @details Su Linux vengono utilizzate le sequenze CSI per spostare il cursore,
//! mentre su Windows si ricava prima la posizione con `GetConsoleScreenBufferInfo`
//! e poi viene aggiornata con `SetConsoleCursorPosition`.
void term_cursor_scroll(int dy);

//! @brief Attende `ms` millisecondi.
//! @details Su Windows viene usata la funzione `Sleep`, mentre su Linux viene
//! usata `select` (in modo da evitare le _Feature Test Macro_).
void term_sleep(unsigned int ms);

//! @brief Legge la larghezza del terminale.
//! @details Su Windows la grandezza viene restituita da `GetConsoleScreenBufferInfo`,
//! mentre su Linux le informazioni vengono richieste con `ioctl`.
unsigned int term_width(void);

//! @brief Legge un carattere senza aspettare il tasto Invio.
//! @details Su Windows viene usata la funzione `_getch` proveniente da `conio.h`,
//! mentre su Linux viene prima disabilitata la modalità _canonica_ per poi leggere
//! il carattere.
char term_getch(void);

#endif
