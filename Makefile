SOURCES = $(wildcard source/**/*.c source/main.c)
OBJECTS = ${SOURCES:.c=.o}

CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iinclude/

.DEFAULT_GOAL = julieDS
all: clean julieDS

.PHONY: clean
clean:
	find . -name '*.o' -type f -delete
	find . -name '*.gch' -type f -delete
	rm -rf build

julieDS: $(SOURCES)
	@mkdir -p build
	@$(CC) $(CFLAGS) $(SOURCES) -o build/$@
	@echo Done