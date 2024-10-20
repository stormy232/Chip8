#include "chip8.hpp"
#include "SDL_PLATFORM.hpp"
#include <chrono>
#include <iostream>
#include <SDL2/SDL.h>


void EmulationLoop(char const *romFilename, int x, int y){

  CPU chip8(romFilename);
  chip8.LoadROM(romFilename);
  SDL_Window* window = Initalize_window(x,y);
  SDL_Renderer* renderer = Initalize_Renderer(window);
  SDL_RenderSetScale(renderer, x/64, y/32);

  bool quit = false;
  int cycle = 0;
  auto start = std::chrono::high_resolution_clock::now();

  while(!quit){
    quit = GetKey(&chip8.key);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> elapsed = end-start;

    if (elapsed.count() > 0.001f){

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
  if (argc < 4){
    std::cout << "Missing Filename or Resolution" << "\n";
    return -1;
  }

  try {
    int x = std::stoi(argv[2]);
    int y = std::stoi(argv[3]);
  }
  catch(std::invalid_argument){
    return -1;
  }
    EmulationLoop(argv[1],std::stoi(argv[2]),std::stoi(argv[3]));
  return 0;
}

