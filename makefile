main:chip8.cpp
	g++ -c cpu.cpp
	g++ -c chip8.cpp
	g++ cpu.o chip8.o -o main `sdl2-config --cflags --libs`
