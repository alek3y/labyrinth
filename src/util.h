//! @file util.h
//! @brief Funzioni varie.

#ifndef UTIL_H
#define UTIL_H

//! @brief Sposta il cursore `dy` colonne.
//! @details Su Linux vengono utilizzate le sequenze CSI per spostare il cursore,
//! mentre su Windows si ricava prima la posizione con `GetConsoleScreenBufferInfo`
//! e poi viene aggiornata con `SetConsoleCursorPosition`.
void cursor_move_rows(int dy);

//! @brief Attende `ms` millisecondi.
//! @details Su Windows viene usata la funzione `Sleep`, mentre su Linux viene
//! usata `select` (in modo da evitare le _Feature Test Macro_).
void msleep(unsigned int ms);

#endif
