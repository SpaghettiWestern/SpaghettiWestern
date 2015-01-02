#include "Renderer.h"

Renderer::Renderer(GameModel& model) : model(model){

}

void Renderer::render(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	render(model);
	glFlush();
}

void Renderer::render(GameModel& model){
	render(model.getGameBoard());
}

void Renderer::render(const GameBoard& gameboard){
	render(gameboard.getBoard());
	for(auto it = gameboard.getSurfaceEffects().begin(); it != gameboard.getSurfaceEffects().end(); ++it){
		render(**it);
	}

}

void Renderer::render(const GameBoardStructure& board){
	for(int i = 0; i < board.getWidth(); i++){
		for(int j = 0; j < board.getLength(); j++){
			render(board.getEnvironmentPiece(i,j));
			if (board.actorExists(i, j)){
				render(*(board.getActor(i,j)));
			}
			if (board.effectsExist(Coordinate(i,j))){
				for(auto it = board.getEffects(Coordinate(i,j)).begin(); it != board.getEffects(Coordinate(i,j)).end(); ++it){
					render((**it));
				}
			}
		}
	}
}


void Renderer::render(const BoardStatic& piece){
	Coordinate piececoord = piece.getLocation();
	ScreenCoordinate botLeft = Util::coordToScreen(piececoord);
	ScreenCoordinate botRight(botLeft.first, botLeft.second+0.05);
	ScreenCoordinate topRight(botLeft.first+0.05, botLeft.second+0.05);
	ScreenCoordinate topLeft(botLeft.first+0.05, botLeft.second);
	auto color = std::make_tuple(botLeft.first, botLeft.second, 0.05);

	drawQuadrangle(botLeft, botRight, topLeft, topRight, color);

}

void Renderer::render(const BoardActor& actor){
	ScreenCoordinate topLeft = actor.getScreenLocation();
	topLeft = ScreenCoordinate(topLeft.first+0.0125, topLeft.second+0.0125);
	ScreenCoordinate botLeft(topLeft.first, topLeft.second+0.025);
	ScreenCoordinate botRight(topLeft.first+0.025, topLeft.second+0.025);
	ScreenCoordinate topRight(topLeft.first+0.025, topLeft.second);

	//auto color = std::make_tuple(0.0, 0.0, 100);
	auto color = actor.getCurrentAnimationFrame().getColor();

	drawQuadrangle(botLeft, botRight, topLeft, topRight, color);
}

void Renderer::render(const Effect& effect){
	ScreenCoordinate topLeft = effect.getScreenLocation();
	topLeft = ScreenCoordinate(topLeft.first+0.0025, topLeft.second+0.0025);
	ScreenCoordinate botLeft(topLeft.first, topLeft.second+0.005);
	ScreenCoordinate botRight(topLeft.first+0.005, topLeft.second+0.005);
	ScreenCoordinate topRight(topLeft.first+0.005, topLeft.second);

	//auto color = std::make_tuple(0.0, 0.0, 100);
	auto color = effect.getCurrentAnimationFrame().getColor();

	drawQuadrangle(botLeft, botRight, topLeft, topRight, color);

}


/**
 * Render a colored quadrangle on the screen
 *
 * @param bottomLeft the bottom left corner of the box
 * @param topRight the top right corner of the box
 * @param color the rgb color percentages of the box
 */
void Renderer::drawQuadrangle(const ScreenCoordinate botLeft, const ScreenCoordinate botRight,
							  const ScreenCoordinate topLeft, const ScreenCoordinate topRight,
							  const std::tuple<float, float, float> color) {
	glBindTexture(GL_TEXTURE_2D, 0);
	glColor3f(std::get<0>(color), std::get<1>(color), std::get<2>(color));

	glBegin(GL_QUADS);
	glVertex2f(botLeft.first, 1-botLeft.second);
	glVertex2f(botRight.first, 1-botRight.second);
	glVertex2f(topRight.first, 1-topRight.second);
	glVertex2f(topLeft.first, 1-topLeft.second);
	glEnd();
}
