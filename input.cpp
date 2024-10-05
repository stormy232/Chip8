#include "chip8.hpp"
#include <iostream>
#include <SDL2/SDL.h>


bool GetKey(uint8_t *a){
SDL_PumpEvents();
SDL_Event e;
*a = 0xFF;
bool quit = false;
  const Uint8* keyboard = SDL_GetKeyboardState(NULL);
          if(keyboard[SDL_SCANCODE_1]){
           *a = 0x0;
            }
          else if(keyboard[SDL_SCANCODE_2]){
           *a = 0x1;
            }
          else if(keyboard[SDL_SCANCODE_3]){
           *a = 0x2;
            }
          else if(keyboard[SDL_SCANCODE_4]){
           *a = 0x3;
            }
          else if(keyboard[SDL_SCANCODE_Q]){
           *a = 0x4;
            }
          else if(keyboard[SDL_SCANCODE_W]){
           *a = 0x5;
            }
          else if(keyboard[SDL_SCANCODE_E]){
           *a = 0x6;
            }
          else if(keyboard[SDL_SCANCODE_R]){
           *a = 0x7;
            }
          else if(keyboard[SDL_SCANCODE_A]){
           *a = 0x8;
            }
          else if(keyboard[SDL_SCANCODE_S]){
           *a = 0x9;
            }
          else if(keyboard[SDL_SCANCODE_D]){
           *a = 0xA;
            }
          else if(keyboard[SDL_SCANCODE_F]){
           *a = 0xB;
            }
          else if(keyboard[SDL_SCANCODE_Z]){
           *a = 0xC;
            }
          else if(keyboard[SDL_SCANCODE_X]){
           *a = 0xD;
            }
          else if(keyboard[SDL_SCANCODE_C]){
           *a = 0xE;
            }
          else if(keyboard[SDL_SCANCODE_V]){
           *a = 0xF;
            }
while (SDL_PollEvent(&e)) {
      switch(e.type){
        case SDL_QUIT:
          quit = true;
          break;
}
}
return quit;
}
void CPU::OP_EX9E(){
  uint8_t VX = registers[(opcode & 0xF00) >> 8];
  std::cout << unsigned(key);
  if (key == VX){
    pc += 2; 
  }
}

void CPU::OP_EXA1(){
  uint8_t VX = registers[(opcode & 0xF00) >> 8];
  std::cout << unsigned(key);
  if (key != VX){
    pc += 2; 
  }
}

void CPU::OP_FX0A(){
      uint8_t *VX = &registers[(opcode & 0xF00) >> 8];
  std::cout << unsigned(key);
 if (key == 0xFF){
  pc -= 2; 
 }
 else{
      *VX=key;
 } 
}
