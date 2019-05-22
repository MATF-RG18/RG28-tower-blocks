PRG = tower-blocks
CC = gcc
CFLAGS = -Wall
GL = -lglut -lGL -lGLU

$(PRG):
	$(CC) -o $(PRG) main.c $(CFLAGS) $(GL)

.PHONY: clean

clean:
	rm $(PRG)
