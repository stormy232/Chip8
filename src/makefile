main:main.cpp cpu.cpp SDL_PLATFORM.cpp
	g++ -c cpu.cpp
	g++ -c main.cpp
	g++ -c SDL_PLATFORM.cpp
	g++ -w cpu.o main.o SDL_PLATFORM.o -o main `sdl2-config --cflags --libs`

clean:
	rm -f *.o
	rm -f main
