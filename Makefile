CC=clang++
STD = -std=c++20
WARNINGS = -Wall -Wextra -pedantic -Wshadow -Wno-pragma-once-outside-header -Wfloat-equal -Wundef -Wcast-align -Wwrite-strings -Wmissing-declarations -Wredundant-decls -Wshadow -Woverloaded-virtual -pedantic
CFLAGS= $(STD) $(WARNINGS)
OBJS= obj/main.o obj/board.o obj/game.o obj/menu.o obj/extras.o
LINKS = -lncurses

main.out: $(OBJS) obj/main.o
	$(CC) $(LINKS) obj/* -o ./main.out

objects: $(OBJS)

obj/main.o: src/main.cpp obj
	$(CC) $(CFLAGS) -c src/main.cpp -o obj/main.o

obj/board.o: src/board.cpp src/board.h obj
	$(CC) $(CFLAGS) -c src/board.cpp -o obj/board.o

obj/menu.o: src/menu.cpp src/menu.h obj
	$(CC) $(CFLAGS) -c src/menu.cpp -o obj/menu.o

obj/game.o: src/game.cpp src/game.h obj
	$(CC) $(CFLAGS) -c src/game.cpp -o obj/game.o

obj/extras.o: src/extras.cpp src/extras.h obj
	$(CC) $(CFLAGS) -c src/extras.cpp -o obj/extras.o

obj: 
	mkdir -p obj

clean:
	rm -r obj
	rm *.out