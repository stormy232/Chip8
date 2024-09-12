#include "chip8.hpp"
#include <SDL2/SDL.h>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <climits>
#include <chrono>
#include <thread>

const unsigned int START_ADDRESS = 0x200;
const unsigned int FONTSET_START_ADDRESS = 0x50;

CPU::CPU() {

  pc = START_ADDRESS;

  for (unsigned int i = 0; i < 80; ++i) {

    memory[FONTSET_START_ADDRESS + i] = fontset[i];
  }
}

void CPU::LoadROM(char const *filename) {

  std::ifstream file(filename, std::ios::binary | std::ios::ate);

  if (file.is_open()) {

    // get size of a file and create a buffer to hold the contents
    std::streampos size = file.tellg();
    char *buffer = new char[size];

    // go to the beggining of the file and fill the buffer
    file.seekg(0, std::ios::beg);
    file.read(buffer, size);
    file.close();

    // load the ROM contents into the Chip8's memory, starting at the 0x200
    for (long i = 0; i < size; ++i) {

      memory[START_ADDRESS + i] = buffer[i];
    }

    std::cout << memory[514];
    // Free the buffer
    delete[] buffer;
  }
}

void CPU::Cycle() {
  opcode = (memory[pc] << 8) | memory[pc + 1];
  pc += 2;
  std::cout << pc << " ";
  switch (opcode & 0xF000) {
  case 0x0000:
    OP_00E0();
    std::cout << "00E0" << '\n';
    break;
  case 0x1000:
    OneNNN();
    std::cout << "1NNN" << '\n';
    break;
  case 0x6000:
    SIXXNN();
    std::cout << "6XNN" << '\n';
    break;
  case 0x7000:
    SevenXNN();
    std::cout << "7XNN" << '\n';
    break;
  case 0xA000:
    ANNN();
    std::cout << "ANNN" << '\n';
    break;
  case 0xD000:
    DXYN();
    std::cout << "DXYN" << '\n';
  }
}

void update(CPU cpu) {
  for (int i = 0; i < 32; i++) {
    std::cout << '\n';
    for (int j = 0; j < 64; j++) {
    int x = cpu.video_buffer[j+64*i];
    if(x == UINT_MAX){
      std::cout << '|';
    }
    else {
      std::cout << x; 
    }
    } 
  }
}

int main(int argc, char *argv[]) {

  CPU cats;
  char const *romFilename = argv[1];
  int videopitch = sizeof(cats.video_buffer[0]) / sizeof(int) * cats.MAX_WIDTH;

  cats.LoadROM(romFilename);
  while (true) { 
    cats.Cycle();
    update(cats);
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  return 1;
}
