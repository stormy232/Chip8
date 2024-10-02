#include "chip8.hpp"
#include <SDL2/SDL.h>

int GetKey(){
SDL_Event e;
while (SDL_PollEvent(&e)) {
    switch (e.type){
      case (SDL_KEYDOWN):
        std::cout << e.key.keysym.sym << '\n';
        switch (e.key.keysym.sym){
          case(48): 
            return 0x0;
          case(49): 
            return 0x1;
          case(50): 
            return 0x2;
          case(51): 
            return 0x3;
          case(52): 
            return 0x4;
          case(53): 
            return 0x5;
          case(54): 
            return 0x6;
          case(55): 
            return 0x7;
          case(56): 
            return 0x8;
          case(57): 
            return 0x9;
          case(97): 
            return 0xA;
          case(98): 
            return 0xB;
          case(99): 
            return 0xC;
          case(100): 
            return 0xD;
          case(101): 
            return 0xE;
          case(102): 
            return 0xF;
    }
  }
}
return -1;
}
void CPU::OP_EX93(){
  uint8_t VX = registers[(opcode & 0xF00) >> 8];
  if (GetKey == VX){
    pc += 2; 
  }
}

void CPU::OP_EX93(){
  uint8_t VX = registers[(opcode & 0xF00) >> 8];
  if (GetKey != VX){
    pc += 2; 
  }
}

void CPU::OP_FX0A(){
 if (GetKey() == -1){
  pc -= 2; 
 }
 else {
  uint8_t *VX = registers[(opcode & 0xF00) >> 8];
  *VX=GetKey();
 }
}
