//! @file util.h
//! @brief Funzioni varie.

#ifndef UTIL_H
#define UTIL_H

//! @brief Stampa la stringa in base a `format` pulendo il resto della riga.
//! @details Non conoscendo la posizione orizzontale del cursore la stampa
//! viene effettuata all'inzio della riga con '\r'.
//! @return I byte stampati a video (solo quelli stampati con `format`).
int printf_clean(char *format, ...);

#endif
