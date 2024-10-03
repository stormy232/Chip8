#include <SDL2/SDL.h>
#include <iostream>
#include "chip8.hpp"
#include <unistd.h>

SDL_Window* Initalize_window(int scale){
  if(SDL_Init(SDL_INIT_VIDEO) != 0){
    std::cout << "Error" << SDL_GetError();
  }
  return SDL_CreateWindow("Tester",0,0,1920,1080,SDL_WINDOW_SHOWN);
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
      SDL_RenderSetScale(renderer, 15, 20);
    
    for (int i=0; i<32; i++) {  
      for (int j = 0; j<64; j++) {
        if (video_buffer[i*64+j] != 0){
        SDL_RenderDrawPoint(renderer,j,i);
        }
      }
    }

   SDL_RenderPresent(renderer);
}

void EmulationLoop(char const *romFilename){
  CPU chip8;
  chip8.LoadROM(romFilename);
  SDL_Window* window = Initalize_window(1);
  SDL_Renderer* renderer = Initalize_Renderer(window);
  bool quit = true;
  int cycle = 0;
  auto start = std::chrono::high_resolution_clock::now();
  while(quit){
    chip8.Cycle();
    update_screen(window,renderer,chip8.video_buffer);
    if (cycle % 8 == 0){
      if (chip8.soundtimer){
        std::cout << "Soundtimer: " << unsigned(chip8.soundtimer) << '\n';
        chip8.soundtimer--;
      }
      if (chip8.timer) {
        std::cout << "timer: " << unsigned(chip8.timer) << '\n';
        chip8.timer--;
      }
    }
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
       if (e.type == SDL_QUIT) {
         quit = false;
         break;
      }
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> elapsed = end-start;
    usleep(2000-elapsed.count());
  }
  Destroy_Window_And_Renderer(window,renderer);
}

int main(int argc, char *argv[]) {

  if (argc < 2){
    std::cout << "Missing Filename" << "\n";
    return -1;
  }
  EmulationLoop(argv[1]);
  return 1;
}
