#pragma once

#include <SDL.h>

class Paddle {
public:
	Paddle(const SDL_Keycode up, const SDL_Keycode down, const Uint32 colour, int width, int height, int windowHeight, int windowWidth, int startX);
	void draw(Uint32 *buffer);
	void move(const Uint8* keystate);
	int _x = 0;
	int _y = 0;
	int _width = 10;
	int _height = 40;

private:
	SDL_Keycode _moveUp = SDLK_UP;
	SDL_Keycode _moveDown = SDLK_DOWN;
	int _windowHeight;
	int _windowWidth;
	Uint32 _colour = 0xFFFFFFFF;
};

class Ball {
public:
	Ball(const Uint32 colour, int width, int height, int windowHeight, int windowWidth, int startVelX, int startVelY);
	void draw(Uint32 *buffer);
	void progress(const Paddle * p1, const Paddle * p2);
	int _width = 20;
	int _height = 20;
	int _x = 0;
	int _y = 0;

private:
	int _velX = 0;
	int _velY = 0;
	int _windowHeight;
	int _windowWidth;
	Uint32 _colour = 0xFFFFFFFF;
};