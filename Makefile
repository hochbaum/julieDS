SOURCES = $(shell find ./source -name *.c -type f)
OBJECTS = ${SOURCES:.c=.o}

CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iinclude/ -lraylib

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

.PHONY: run
run: julieDS
	chmod +x build/julieDS
	build/julieDS res/TinyFB.nds