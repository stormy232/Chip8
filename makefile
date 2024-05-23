main:chip8.cpp
	g++ -o main chip8.cpp `sdl2-config --cflags --libs`
