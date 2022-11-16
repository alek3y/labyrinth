CC = gcc
CFLAGS = -g -std=c99 -pedantic -Wall -Wextra -Wshadow
CFLAGS += -Wno-unused-but-set-variable -Wno-missing-field-initializers

SRC = $(wildcard src/*.c)
BIN := bin/game

ifeq ($(OS),Windows_NT)
	BIN := $(BIN).exe
	BINDIR = "$(BIN)/.."
else
	BINDIR = $(shell dirname "$(BIN)")
endif

# Lista dei target non-file
.PHONY: all docs clean

all: $(BINDIR) $(BIN)

$(BINDIR):
	-mkdir $(BINDIR)

# La variabile automatica $@ è il target,
# e $^ sono i prerequisiti (file .c)
$(BIN): $(SRC)
	$(CC) $(CFLAGS) $^ -o $@

docs:
	doxygen

clean:
ifeq ($(OS),Windows_NT)
	-rd /s /q $(BINDIR) docs
else
	-rm -r $(BINDIR) docs
endif
