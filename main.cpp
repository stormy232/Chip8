#include <SDL2/SDL.h>
#include <iostream>
#include "chip8.hpp"
#include <thread>
#include <chrono>
#include <climits>

void Initalize_window(int scale, CPU &cats){
  if(SDL_Init(SDL_INIT_VIDEO) != 0){
    std::cout << "Error" << SDL_GetError();
  }
  else{
    SDL_Window* window;
    SDL_Renderer* renderer;
    window = SDL_CreateWindow("Tester",0,0,800,600,SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window,0,0);

    SDL_RenderSetScale(renderer,10,15);
    bool quit = true; 

    while (quit == true){
      SDL_Event e;
      SDL_SetRenderDrawColor(renderer,0,0,0,255);    
      SDL_RenderClear(renderer);
      SDL_SetRenderDrawColor(renderer,255,255,255,255);
    
    for (int i=0; i<32; i++) {  
      for (int j = 0; j<64; j++) {
        if (cats.video_buffer[i*64+j] != 0){
        SDL_RenderDrawPoint(renderer,j,i);
        }
      }
    }

   SDL_RenderPresent(renderer);
   cats.Cycle();

   while (SDL_PollEvent(&e)) {
     if (e.type == SDL_QUIT) {
       quit = false;
       break;
     }
   }

   SDL_Delay(500);
 }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
  }

  }



/* void drawing(int scale, uint32_t (&video)[64*32])
{
  while (!SDL_QUIT) {
    SDL_SetRenderDrawColor(renderer,0,0,0,255);    
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    
    for (int i=0; i<32; i++) {

      for (int j =0; j<64; j++) {
        SDL_RenderDrawPoint(renderer,j,i);
        SDL_RenderPresent(renderer);
        SDL_Delay(10000);
      }
    }

  }
  SDL_DestroyWindow(window);
  SDL_Quit();

}
*/

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
  //int videopitch = sizeof(cats.video_buffer[0]) / sizeof(int) * cats.MAX_WIDTH;
  cats.LoadROM(romFilename);
  Initalize_window(1.25,cats);
  
  return 1;
}
