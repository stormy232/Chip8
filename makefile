main:chip8.cpp
	g++ -I src/include -L src/lib -o main main.cpp -lmingw32 -lSDL2main -lsDl2
