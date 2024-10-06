#include <SDL2/SDL.h>

SDL_Window* Initalize_window(int scale);
SDL_Renderer* Initalize_Renderer(SDL_Window* window);
void Destroy_Window_And_Renderer(SDL_Window* window, SDL_Renderer* renderer);
void update_screen(SDL_Window* window,SDL_Renderer* renderer,uint32_t (&video_buffer)[64*32]);
bool GetKey(uint8_t *a);
