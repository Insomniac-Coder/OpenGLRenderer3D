#pragma once
#include <string>
#include "glew.h"
#include <SDL.h>
#include <iostream>

class Display {
public:
	Display(int width, int height, const std::string& title);
	void Update();
	void Clear(float red, float green, float blue, float alpha);
	bool WindowClosed();
	virtual ~Display();

private:
	SDL_Window* window;
	SDL_GLContext Glcontext;
	bool isClosed;

	Display(const Display& other) {}
	Display& operator=(const Display& other) {}
};