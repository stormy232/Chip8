main:main.cpp cpu.cpp input.cpp
	g++ -c cpu.cpp
	g++ -c main.cpp
	g++ -c input.cpp
	g++ cpu.o main.o input.o -o main `sdl2-config --cflags --libs`
