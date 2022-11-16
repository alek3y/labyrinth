//! @file util.h
//! @brief Funzioni varie.

#ifndef UTIL_H
#define UTIL_H

//! @brief Stampa la stringa in base a `format` pulendo il resto della riga.
//! @return Il numero di byte stampati a video (quelli stampati con `format`).
int printf_clean(char *format, ...);

#endif
