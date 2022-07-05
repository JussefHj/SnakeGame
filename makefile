all : clean snake.exe

snake.exe : snake.o logic.o
	gcc snake.o logic.o -o snake.exe `sdl2-config --cflags --libs`

snake.o   : snake.c
	gcc -c snake.c 
	
logic.o   : logic.c logic.h 
	gcc -c logic.c 
	
clean :
	rm -f *.o
