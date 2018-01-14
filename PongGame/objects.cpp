#include <SDL.h>
#include "objects.h"

Paddle::Paddle(const SDL_Keycode up, const SDL_Keycode down, const Uint32 colour, int width, int height, int windowHeight, int windowWidth, int startX) :
_moveUp(up), _moveDown(down), _height(height), _width(width), _x(startX), _y((windowHeight-height)/2), _colour(colour), _windowHeight(windowHeight), _windowWidth(windowWidth)
{}

void Paddle::draw(Uint32 *buffer) {
	for (int y = 0; y < _height; y++) {
		for (int x = 0; x < _width; x++) {
			buffer[(y + _y)*_windowWidth + x + _x] = _colour;
		}
	}
}

void Paddle::move(const Uint8* keystate) {
	if (keystate[_moveUp]) {
		_y -= 2;
	}
	if (keystate[_moveDown]) {
		_y += 2;
	}
	if (_y < 0) {
		_y = 0;
	}
	if (_y > _windowHeight - _height) {
		_y = _windowHeight - _height;
	}
}

Ball::Ball(const Uint32 colour, int width, int height, int windowHeight, int windowWidth, int startVelX, int startVelY) :
_colour(colour), _width(width), _height(height), _windowHeight(windowHeight), _windowWidth(windowWidth), _x((windowWidth-width)/2), _y((windowHeight-height)/2), _velX(startVelX), _velY(startVelY)
{}

void Ball::draw(Uint32 *buffer) {
	for (int y = 0; y < _height; y++) {
		for (int x = 0; x < _width; x++) {
			buffer[(y + _y)*_windowWidth + x + _x] = _colour;
		}
	}
}

void Ball::progress(const Paddle * p1, const Paddle * p2) {
	if (_x+_width >= p2->_x && _x <= p2->_x+p2->_width && _y+_height >= p2->_y && _y <= p2->_y+p2->_height) {
		if (_x > p2->_x + (p2->_width / 2)) {
			_velX = 2;
		}
		if (_x <= p2->_x + (p2->_width / 2)) {
			_velX = -2;
		}
		_velY = round((_y - (p2->_y + p2->_height/2))/20);
	}
	if (_x + _width >= p1->_x && _x <= p1->_x + p1->_width && _y + _height >= p1->_y && _y <= p1->_y + p1->_height) {
		if (_x > p1->_x + (p1->_width / 2)) {
			_velX = 2;
		}
		if (_x <= p1->_x + (p1->_width / 2)) {
			_velX = -2;
		}
		_velY = round((_y - (p1->_y + p1->_height / 2))/20);
	}
	if (_velY == 0) {
		_velY = 1;
	}
	_x += _velX;
	_y += _velY;
	if (_x <= 0) {
		_x = 0;
		_velX = -_velX;
	}
	if (_x >= _windowWidth-_width) {
		_x = _windowWidth-_width;
		_velX = -_velX;
	}
	if (_y <= 0) {
		_y = 0;
		_velY = -_velY;
	}
	if (_y >= _windowHeight - _height) {
		_y = _windowHeight - _height;
		_velY = -_velY;
	}

}