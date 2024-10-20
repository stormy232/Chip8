#include <SDL2/SDL.h>
#include <iostream>
#include <unistd.h>

SDL_Window* Initalize_window(int x, int y){
  if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
    std::cout << "Error" << SDL_GetError();
  }
  return SDL_CreateWindow("Tester",0,0,x,y,SDL_WINDOW_SHOWN);
}

SDL_Renderer* Initalize_Renderer(SDL_Window* window){
    return SDL_CreateRenderer(window,0,0);
}

void Destroy_Window_And_Renderer(SDL_Window* window, SDL_Renderer* renderer){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
void update_screen(SDL_Window* window, SDL_Renderer* renderer, uint32_t (&video_buffer)[64*32]){
      SDL_SetRenderDrawColor(renderer,0,0,0,255);    
      SDL_RenderClear(renderer);
      SDL_SetRenderDrawColor(renderer,255,255,255,255);
    
    for (int i=0; i<32; i++) {  
      for (int j = 0; j<64; j++) {
        if (video_buffer[i*64+j] != 0){
        SDL_RenderDrawPoint(renderer,j,i);
        }
      }
    }

   SDL_RenderPresent(renderer);
}

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
