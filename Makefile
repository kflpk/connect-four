CC=g++
CFLAGS= -Wall -Wextra -Wfloat-equal -Wundef -Wcast-align -Wwrite-strings -Wlogical-op -Wmissing-declarations -Wredundant-decls -Wshadow -Woverloaded-virtual
OBJS= main.o board.o

objects: $(OBJS)

main.o: src/main.cpp obj
	g++ $(CFLAGS) -c src/main.cpp -o obj/main.o

board.o: src/board.cpp obj
	g++ $(CFLAGS) -c src/board.cpp -o obj/board.o

menu.o: src/menu.cpp obj
	g++ $(CFLAGS) -c src/menu.cpp -o obj/menu.o

game.o: src/game.cpp obj
	g++ $(CFLAGS) -c src/game.cpp -o obj/game.o

obj:
	mkdir -p obj

clean:
	rm -r obj