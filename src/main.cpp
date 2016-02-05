#define _USE_MATH_DEFINES
#include <math.h>

#include <iostream>
#include <utility>
#include <vector>
#include <memory>
#include <stdexcept>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
//#include <SDL2/SDL_ttf.h>

#include <GL/gl.h>
#include <GL/glu.h>

#include "Util.h"
#include "GameModel.h"
#include "GameView.h"
#include "GameController.h"
#include "BlitHelper.h"

/**
 * Initialize some OpenGL settings.
 */
void initOpenGL() {
	glEnable(GL_TEXTURE_2D);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(1.f, 1.f, 1.f, 1.f);
	glDepthFunc(GL_NEVER);
}

/**
 * Reset the viewport after a window resize.
 * @param width The new width of the viewport.
 * @param height The new height of the viewport.
 */
void updateViewport(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity ();
	gluOrtho2D(0, 1, 0, 1);

	glMatrixMode(GL_MODELVIEW);
}

/**
 * Run the game loop until the game exits.
 * @param displayWindow The window the game is being drawn in.
 * @param view The view of the game being drawn.
 */
void gameLoop(SDL_Window& displayWindow, GameView& view, GameController& controller) {
	bool running = true;
	while(running) {
		SDL_Event event;
		while(SDL_PollEvent(&event)) {
			running = controller.handleInput(event);
		}

		view.render();

		SDL_GL_SwapWindow(&displayWindow);
		//To keep my computer from running at maximum
		SDL_Delay(10);
	}
}

/**
 * Check the renderer created by SDL is valid for our purposes (uses accelerated graphics).
 * @param displayRenderer The renderer being used for the game.
 * @return If the renderer is valid.
 */
bool checkSDLRenderer(SDL_Renderer& displayRenderer) {
	SDL_RendererInfo displayRendererInfo;
	SDL_GetRendererInfo(&displayRenderer, &displayRendererInfo);
	return (displayRendererInfo.flags & SDL_RENDERER_ACCELERATED) && (displayRendererInfo.flags & SDL_RENDERER_TARGETTEXTURE);
}


/**
 * Initialize the game objects, and run the game loop.
 */
void startGame() {
	std::cout << "starting\n";

	SDL_Window* displayWindow = SDL_CreateWindow("Spaghetti Western", 20.0, 60.0, 800.0, 600.0, SDL_WINDOW_OPENGL);
	SDL_Renderer* displayRenderer = SDL_CreateRenderer(displayWindow, -1, SDL_RENDERER_ACCELERATED);


	if(checkSDLRenderer(*displayRenderer)) {}
	else {
		std::cerr << "Unable to create a rendering window using accelerated graphics." << std::endl;
		return;
	}

	SDL_GLContext glContext = SDL_GL_CreateContext(displayWindow);

	initOpenGL();

	updateViewport(800, 600);//getGraphicsConfig()["screen.width"], getGraphicsConfig()["screen.height"]);

	BlitHelper::initilize_blitter(displayRenderer);

	GameModel model(20,20, {std::make_pair("P1", true), std::make_pair("P2", true)});
	model.createActor(Coordinate(0,0), 0, 28, Attack(28, 1.0, .05, .003));
	model.createActor(Coordinate(2,2), 1, 42, Attack(42, .85, .1, .001));
	model.createWall(Coordinate(5,5), -1);
	model.createWall(Coordinate(5,6), -1);
	model.playMovingEffect(ScreenCoordinate(0,0), ScreenCoordinate(1,1), true);
	model.playMovingEffect(ScreenCoordinate(0,.95), ScreenCoordinate(.95,0), false);

	GameView view(model);
	GameController controller(model);

	gameLoop(*displayWindow, view, controller);

	SDL_DestroyWindow(displayWindow);
	SDL_DestroyRenderer(displayRenderer);
	SDL_GL_DeleteContext(glContext);
}


int main(int argc, char *argv[]) {
	std::cout << "program begin\n";

	/*if(TTF_Init()==-1) {
		std::cerr << "Error in TTF_Init: " << TTF_GetError() << std::endl;
		return 2;
	}*/

	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_NOPARACHUTE) < 0) {
		std::cerr << "Error in SDL_Init: " << SDL_GetError() << std::endl;
		return -1;
	}

	startGame();

	SDL_Quit();
	return 0;
}
