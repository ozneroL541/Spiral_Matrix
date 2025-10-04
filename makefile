BIN=bin
CFLAGS= -Wall -Werror -Wextra -ansi -pedantic -Wuninitialized -Wno-unused-parameter -O3
LIBS = -lm
SRC = src
_OUTPUT = spiral_matrix
OUTPUT = $(BIN)/$(_OUTPUT)
ICX := $(shell command -v icx 2>/dev/null)
ifeq ($(ICX),)
    CC := gcc
else
    CC := icx
endif

$(shell mkdir -p $(BIN))

$(OUTPUT): $(SRC)/main.c
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
