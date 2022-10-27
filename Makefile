CC = cc
CFLAGS = -std=c99 -pedantic -Wall -Wextra -Wshadow

SRC = $(wildcard src/*.c)
BUILD = bin/game

all: dirs $(BUILD)

dirs:
	mkdir -p $$(dirname "$(BUILD)")

# Automatic variable $@ is the target,
# and $^ are the prerequisites (.c files)
$(BUILD): $(SRC)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	-rm -r $$(dirname "$(BUILD)")
