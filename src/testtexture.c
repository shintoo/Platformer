#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>
#include "texture.h"

int main(void) {
	SDL_Window *window;
	SDL_Renderer *renderer;
	Texture *background;
	Texture *sprite;
	SDL_Event e;
	SDL_Rect screen = {0, 0, 640, 480};
	bool running = true;

	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);

	window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen.w, screen.h, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);

	sprite = New_Texture(renderer, "sprite.png");
	background = New_Texture(renderer, "background.png");

	while (running) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_KEYDOWN) {
				running = false;
			}
		}
		
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);

		Texture_Render(background, renderer, 0, 0);
		Texture_Render(sprite, renderer, screen.w / 2 - sprite->w / 2, screen.h / 2 - sprite->h / 2);

		SDL_RenderPresent(renderer);
	}

	Destroy_Texture(background);
	Destroy_Texture(sprite);

	SDL_Quit();
	IMG_Quit();

	return 0;
}
