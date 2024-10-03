#include "chip8.hpp"
#include <iostream>
#include <SDL2/SDL.h>

uint8_t GetKey(){
SDL_PumpEvents();
SDL_Event e;
while (SDL_PollEvent(&e)) {
    switch (e.type){
      case (SDL_KEYDOWN):
        std::cout << "Key Pressed";
        switch (e.key.keysym.sym){
          case(SDLK_1): 
            return 0x0;
          case(SDLK_2): 
            return 0x1;
          case(SDLK_3): 
            return 0x2;
          case(SDLK_4): 
            return 0x3;
          case(SDLK_q): 
            return 0x4;
          case(SDLK_w): 
            return 0x5;
          case(SDLK_e): 
            return 0x6;
          case(SDLK_r): 
            return 0x7;
          case(SDLK_a): 
            return 0x8;
          case(SDLK_s): 
            return 0x9;
          case(SDLK_d): 
            return 0xA;
          case(SDLK_f): 
            return 0xB;
          case(SDLK_z): 
            return 0xC;
          case(SDLK_x): 
            return 0xD;
          case(SDLK_c): 
            return 0xE;
          case(SDLK_v): 
            return 0xF;
    }
  }
}
return -1;
}
void CPU::OP_EX9E(){
  uint8_t VX = registers[(opcode & 0xF00) >> 8];
  if (GetKey() == VX){
    pc += 2; 
  }
}

void CPU::OP_EXA1(){
  uint8_t VX = registers[(opcode & 0xF00) >> 8];
  if (GetKey() != VX){
    pc += 2; 
  }
}

void CPU::OP_FX0A(){
 if (GetKey() == -1){
  pc -= 2; 
 }
 else {
  uint8_t *VX = &registers[(opcode & 0xF00) >> 8];
  *VX=GetKey();
 }
}
