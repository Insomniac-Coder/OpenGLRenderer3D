#include "display.h"

Display::Display(int width, int height, const std::string& title) {
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	Glcontext = SDL_GL_CreateContext(window);

	GLenum GLstatus = glewInit();

	if (GLstatus != GLEW_OK) {
		std::cerr << "GLEW Initialization Failed!" << std::endl;
	}
	isClosed = false;
}

Display::~Display() {
	SDL_GL_DeleteContext(Glcontext);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

bool Display::WindowClosed() {
	return isClosed;
}

void Display::Update() {
	SDL_GL_SwapWindow(window);

	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			isClosed = true;
		}
	}
}

void Display::Clear(float red, float green, float blue, float alpha) {
	glClearColor(0.0f, 0.15f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}