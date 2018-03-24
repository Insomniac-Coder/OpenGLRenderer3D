#include "display.h"

Display::Display(int width, int height, const std::string& title) {
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	Glcontext = SDL_GL_CreateContext(window);

	GLenum GLstatus = glewInit();

	if (GLstatus != GLEW_OK) {
		std::cerr << "GLEW Initialization Failed!" << std::endl;
	}
	isClosed = false;

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

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
		if (event.type == SDL_KEYDOWN){
			 switch(event.key.keysym.sym) {
			 case SDLK_w:
				 CamMovement = 1.f;
				 break;
			 case SDLK_s:
				 CamMovement = -1.f;
				 break;
			 case SDLK_a:
				 CamMovement = 0.5f;
				 break;
			 case SDLK_d:
				 CamMovement = -0.5f;
				 break;
			 case SDLK_SPACE:
				 movement = !movement;
				 break;
			}
		}
		if (event.type == SDL_KEYUP) {
			CamMovement = 0;
		}
		//std::cout << CamMovement << std::endl;
	}
}

void Display::Clear(float red, float green, float blue, float alpha) {
	glClearColor(red, green, blue, alpha);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}