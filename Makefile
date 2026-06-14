CC = gcc
CFLAGS = -Wall -Wextra -std=c11
OBJ = main.o utils.o commands.o

editor: $(OBJ)
	$(CC) $(CFLAGS) -o editor $(OBJ)

main.o: main.c $(DEPS)
	$(CC) $(CFLAGS) -c main.c

utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c utils.c

commands.o: commands.c commands.h
	$(CC) $(CFLAGS) -c commands.c

clean:
	del /Q *.o editor.exe 2>nul || true

.PHONY: clean