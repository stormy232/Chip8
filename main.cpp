#include <SDL2/SDL.h>
#include <iostream>

void drawing(int scale)
{
    SDL_Window* window=nullptr;
    SDL_Renderer* renderer = nullptr;

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(64*scale,32*scale,0,&window, &renderer);
    SDL_RenderSetScale(renderer,scale,scale);
    SDL_SetRenderDrawColor(renderer,0,0,0,255);    
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer,255,255,255,255);

    SDL_RenderDrawPoint(renderer,0,0);

    SDL_RenderPresent(renderer);
    SDL_Delay(10000);
}

