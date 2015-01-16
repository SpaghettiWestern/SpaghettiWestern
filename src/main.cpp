#define _USE_MATH_DEFINES
#include <math.h>

#include <iostream>
#include <utility>
#include <vector>
#include <memory>
#include <stdexcept>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_ttf.h>

#include <GL/gl.h>
#include <GL/glu.h>

#include "Util.h"
#include "GameModel.h"
#include "GameView.h"
#include "GameController.h"

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
 * Construct a resource unique_ptr, given a constructor, destructor, and arugments.
 * Intended for use with C-style constructor and destructor functions that operate on pointers.
 * From http://ericscottbarr.com/blog/2014/04/c-plus-plus-14-and-sdl2-managing-resources/
 * @param c The creator/initialization function.
 * @param d The destructor function
 * @param args The arguments to give to the constructor.
 * @return A unique pointer to the constructed resource.
 */
template<typename Creator, typename Destructor, typename... Arguments>
auto make_resource(Creator c, Destructor d, Arguments&&... args)
-> std::unique_ptr<typename std::decay<decltype(*c(std::forward<Arguments>(args)...))>::type, void(*)(typename std::decay<decltype(*c(std::forward<Arguments>(args)...))>::type*)>
{
	auto r = c(std::forward<Arguments>(args)...);
	if (!r) { throw std::runtime_error {"Unable to create resource"}; }
	typedef typename std::decay<decltype(*r)>::type ResourceType;
	return std::unique_ptr<ResourceType, void(*)(ResourceType*)>(r, d);
}



/**
 * Initialize the game objects, and run the game loop.
 */
void startGame() {
	std::cout << "starting\n";

	auto displayWindow = make_resource(SDL_CreateWindow, SDL_DestroyWindow,
		"Spaghetti Western",
		20.0,//(float)getGraphicsConfig()["screen.x"],
		60.0,//(float)getGraphicsConfig()["screen.y"],
		800.0,//(float)getGraphicsConfig()["screen.width"],
		600.0,//(float)getGraphicsConfig()["screen.height"],
		SDL_WINDOW_OPENGL);

	auto displayRenderer = make_resource(SDL_CreateRenderer, SDL_DestroyRenderer,
		displayWindow.get(),
		-1,
		SDL_RENDERER_ACCELERATED);

	if(checkSDLRenderer(*displayRenderer)) {}
	else {
		std::cerr << "Unable to create a rendering window using accelerated graphics." << std::endl;
		return;
	}

	SDL_GLContext glContext = SDL_GL_CreateContext(displayWindow.get());

	initOpenGL();

	updateViewport(800, 600);//getGraphicsConfig()["screen.width"], getGraphicsConfig()["screen.height"]);

	GameModel model(20,20, {std::make_pair("P1", true), std::make_pair("P2", true)});
	model.createActor(Coordinate(0,0), 0, 28, Attack(28, 1.0, .05, .003));
	model.createActor(Coordinate(2,2), 1, 42, Attack(42, .85, .1, .001));
	model.playMovingEffect(ScreenCoordinate(0,0), ScreenCoordinate(1,1), true);
	model.playMovingEffect(ScreenCoordinate(0,.95), ScreenCoordinate(.95,0), false);

	GameView view(model);
	GameController controller(model);

	gameLoop(*displayWindow, view, controller);

	SDL_GL_DeleteContext(glContext);
}


int main(int argc, char *argv[]) {
	std::cout << "program begin\n";

	if(TTF_Init()==-1) {
		std::cerr << "Error in TTF_Init: " << TTF_GetError() << std::endl;
		return 2;
	}

	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_NOPARACHUTE) < 0) {
		std::cerr << "Error in SDL_Init: " << SDL_GetError() << std::endl;
		return -1;
	}

	startGame();

	SDL_Quit();
	return 0;
}
