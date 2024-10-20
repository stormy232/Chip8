#include <SDL2/SDL.h>
#include <iostream>
#include <unistd.h>

SDL_Window* Initalize_window(int x, int y){
  if(SDL_Init(SDL_INIT_EVERYTHING) != 0){ //Check if SDL properly Initalizes
    std::cout << "Error" << SDL_GetError();
  }
  return SDL_CreateWindow("Tester",0,0,x,y,SDL_WINDOW_SHOWN); //Create a SDL Window with the specified resolution x (width of window) and y (height of the window)
}

SDL_Renderer* Initalize_Renderer(SDL_Window* window){
    return SDL_CreateRenderer(window,0,0); //Create a renderer with a pointer to the window created above
}

void Destroy_Window_And_Renderer(SDL_Window* window, SDL_Renderer* renderer){ //Handle Cleanup of all SDL Components after the user quits the program
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
void update_screen(SDL_Window* window, SDL_Renderer* renderer, uint32_t (&video_buffer)[64*32]){ //Handles the Drawing Component of the interpreter (DXYN)
      SDL_SetRenderDrawColor(renderer,0,0,0,255);    //Could change to make the background colour of the interpreter up to the user
      SDL_RenderClear(renderer); //Sets all pixels of the renderer to the colour specified above
      SDL_SetRenderDrawColor(renderer,255,255,255,255);
    
   //Loop through the video_buffer and draws all sprites that are 1 (ON) 
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
	//Could also implement the following as adding to an array of keys but it doesn't really change behaviour much
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

  //Check if the user closed the window
  while (SDL_PollEvent(&e)) {
        switch(e.type){
          case SDL_QUIT:
            quit = true;
            break;
        }
    }
  return quit; //Returns whether or not the user closed the window
}
