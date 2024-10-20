#include "chip8.hpp"
#include "SDL_PLATFORM.hpp"
#include <chrono>
#include <iostream>
#include <SDL2/SDL.h>


void EmulationLoop(char const *romFilename, int x, int y){

  CPU chip8(romFilename); //Create object of Class CPU and give it the path to our rom
  chip8.LoadROM(romFilename); //Read Rom into memory
  //Following three Functions defined within SDL_PLATFORM.CPP
  SDL_Window* window = Initalize_window(x,y); 
  SDL_Renderer* renderer = Initalize_Renderer(window);
  SDL_RenderSetScale(renderer, x/64, y/32);

  bool quit = false; //Check for user closing the window
  int cycle = 0;
  auto start = std::chrono::high_resolution_clock::now(); //gives current time (needed to implement delay timing at 60Hz)

  while(!quit){
    quit = GetKey(&chip8.key);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> elapsed = end-start;

    if (elapsed.count() > 0.002f){ //Run at 1000Hz (Other ways I've seen people implement this is by running the main loop at 60Hz and simply doing x instructions instead)
	//Run a Cycle and Update the Screen
        chip8.Cycle();
        update_screen(window,renderer,chip8.video_buffer);

        if (cycle % 16 == 0){ //Delay timers have to be reduced at 60Hz 
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
    std::cout << "Missing Arguments" << "\n" << "./main [romfilename] [resolution_width] [resolution_height]" << '\n';
    return -1;
  }
 //Try Catch Loop To Ensure that User is typing in an actual number for a resolution so program doesn't seg fault
  try {
    int x = std::stoi(argv[2]);
    int y = std::stoi(argv[3]);
    if (x < 1 or y < 1){
	throw std::invalid_argument("Resolution Lower that 1.");
    }
  }
  catch(std::invalid_argument){
    std::cout << "Invalid Resolution\n";
    return -1;
  }
    EmulationLoop(argv[1],std::stoi(argv[2]),std::stoi(argv[3]));
  return 0;
}

