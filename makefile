main:chip8.cpp
	g++ -c cpu.cpp
	g++ -c main.cpp
	g++ cpu.o main.o -o main `sdl2-config --cflags --libs`
