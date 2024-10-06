#include "chip8.hpp"
#include "SDL_PLATFORM.hpp"
#include <chrono>
#include <iostream>
#include <SDL2/SDL.h>


void EmulationLoop(char const *romFilename){
  CPU chip8(romFilename);
  SDL_Window* window = Initalize_window(1);
  SDL_Renderer* renderer = Initalize_Renderer(window);
  //make this configurable 
  SDL_RenderSetScale(renderer, 15, 20);

  bool quit = false;
  int cycle = 0;
  auto start = std::chrono::high_resolution_clock::now();

  while(!quit){
    quit = GetKey(&chip8.key);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> elapsed = end-start;
    if (elapsed.count() > 0.002f){
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
        cycle++;
        start=end;
    }
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

