//! @file util.h
//! @brief Funzioni varie.

#ifndef UTIL_H
#define UTIL_H

//! @brief Stampa la stringa da `offset` secondo `format` pulendo il resto della riga.
//! @return Il numero di byte stampati con `format` a video.
int printf_clean(unsigned int offset, char *format, ...);

#endif
