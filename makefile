CC = gcc
CFILES = *.c
HFILES = *.h
MAIN = juego.c
OBJETOS = animos.o archivos.o comandos.o defendiendo_torres.o graficos.o utiles.o
FILES = Enunciado README.md makefile MAKEFILE.md
EXEC = defendiendo
CFLAGS =  -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0
GFLAGS = --tui
VFLAGS = --leak-check=full --track-origins=yes --show-reachable=yes 

$(EXEC): $(MAIN) $(OBJETOS)
	$(CC) $^ $(CFLAGS) -o $(EXEC)

debug: $(EXEC)
	gdb $(GFLAGS) $(EXEC)

test: $(EXEC)
	valgrind $(VFLAGS) ./$(EXEC) $(arg_1) $(arg_2) $(arg_3)

run: $(EXEC)
	./$(EXEC) $(arg_1) $(arg_2) $(arg_3)

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

zip: 
	zip -r $(EXEC).zip $(CFILES) $(HFILES) $(FILES)

.PHONY: clean
clean:
	rm -f $(EXEC)