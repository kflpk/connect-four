CC=clang++
STD = -std=c++20
WARNINGS = -Wall -Wextra -pedantic -Wshadow -Wno-pragma-once-outside-header -Wfloat-equal -Wundef -Wcast-align -Wwrite-strings -Wmissing-declarations -Wredundant-decls -Wshadow -Woverloaded-virtual -pedantic
CFLAGS= $(STD) $(WARNINGS)
OBJS= main.o board.o game.o menu.o
LINKS = -lncurses

default: objects
	$(CC) $(LINKS) obj/* -o ./main.out

objects: $(OBJS)

main.o: src/main.cpp obj
	$(CC) $(CFLAGS) -c src/main.cpp -o obj/main.o

board.o: src/board.cpp obj
	$(CC) $(CFLAGS) -c src/board.cpp -o obj/board.o

menu.o: src/menu.cpp obj
	$(CC) $(CFLAGS) -c src/menu.cpp -o obj/menu.o

game.o: src/game.cpp obj
	$(CC) $(CFLAGS) -c src/game.cpp -o obj/game.o

obj:
	mkdir -p obj

clean:
	rm -r obj
	rm *.out