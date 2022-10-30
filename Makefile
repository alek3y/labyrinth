CC = gcc
CFLAGS = -g -std=c99 -pedantic -Wall -Wextra -Wshadow
CFLAGS += -Wno-unused-but-set-variable

SRC = $(wildcard src/*.c)
BIN = bin/game

BINDIR = $(shell dirname "$(BIN)")

# Lista dei target non-file
.PHONY: all docs clean

all: $(BINDIR) $(BIN)

$(BINDIR):
	mkdir -p $(BINDIR)

# La variabile automatica $@ è il target,
# e $^ sono i prerequisiti (file .c)
$(BIN): $(SRC)
	$(CC) $(CFLAGS) $^ -o $@

docs:
	doxygen

clean:
	-rm -r $(BINDIR) docs
