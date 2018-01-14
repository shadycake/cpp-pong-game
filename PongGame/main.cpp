#include <iostream>
#include <Windows.h>
#include <SDL.h>
#include "objects.h"

const int FRAMERATE = 10;
const int HEIGHT = 480;
const int WIDTH = 720;
const int PADDLE_HEIGHT = 125;
const int PADDLE_WIDTH = 25;
const int PADDLE_PADDING = 10;
const int BALL_SIDE = 20;
const Uint32 BG_COLOUR = 0;
const Uint32 FG_COLOUR = 0xFFFFFFFF;

int main(int argc, char *argv[]) {
	FreeConsole();

	Uint32 *buffer = new Uint32[WIDTH*HEIGHT];

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "SDL_Init Error:" << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Window *window = SDL_CreateWindow(
		"PongGame",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		WIDTH, HEIGHT,
		SDL_WINDOW_ALLOW_HIGHDPI
	);
	if (window == NULL) {
		std::cout << "Failed to create window: " << SDL_GetError() << std::endl;
		return 1;
	}
	
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		std::cout << "Failed to create renderer: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Texture *texture = SDL_CreateTexture(
		renderer, SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_STATIC,
		WIDTH, HEIGHT
	);
	if (texture == NULL) {
		std::cout << "Failed to create texture: " << SDL_GetError() << std::endl;
		return 1;
	}

	
	SDL_UpdateTexture(texture, NULL, buffer, WIDTH * sizeof(Uint32));
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);

	SDL_Event event;
	bool isRunning = true;
	Paddle *p1 = new Paddle(
		SDL_SCANCODE_W, SDL_SCANCODE_S,
		FG_COLOUR,
		PADDLE_WIDTH, PADDLE_HEIGHT,
		HEIGHT, WIDTH, PADDLE_PADDING
	);
	Paddle *p2 = new Paddle(
		SDL_SCANCODE_UP, SDL_SCANCODE_DOWN,
		FG_COLOUR,
		PADDLE_WIDTH, PADDLE_HEIGHT,
		HEIGHT, WIDTH, WIDTH-PADDLE_WIDTH-PADDLE_PADDING
	);
	Ball *ball = new Ball(
		FG_COLOUR,
		BALL_SIDE, BALL_SIDE,
		HEIGHT, WIDTH,
		1, 1
	);
	while (isRunning) {
		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				isRunning = false;
			}
		}
		const Uint8* keystate = SDL_GetKeyboardState(NULL);
		p1->move(keystate);
		p2->move(keystate);
		ball->progress(p1, p2);

		memset(buffer, BG_COLOUR, WIDTH*HEIGHT * sizeof(Uint32));

		p1->draw(buffer);
		p2->draw(buffer);
		ball->draw(buffer);
		if (ball->_x == 0 || ball->_x == WIDTH-ball->_width) {
			isRunning = false;
		}

		SDL_UpdateTexture(texture, NULL, buffer, WIDTH * sizeof(Uint32));
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}