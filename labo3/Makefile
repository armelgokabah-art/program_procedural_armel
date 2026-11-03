CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -pedantic
OBJ = main.o code.o jeu.o
TARGET = codebreaker

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

main.o: main.c jeu.h
	$(CC) $(CFLAGS) -c main.c

code.o: code.c code.h
	$(CC) $(CFLAGS) -c code.c

jeu.o: jeu.c jeu.h code.h
	$(CC) $(CFLAGS) -c jeu.c

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean
