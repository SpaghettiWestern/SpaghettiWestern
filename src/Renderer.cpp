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
			for(int k = 0; k < board.getHeight(); k++){
				render(board.getEnvironmentCell(i,j,k));
			}
		}
	}
}

void Renderer::render(const BoardCell& cell){
	render(*(cell.getFloor()));
	for(int i = 0; i < 4; i++){
		render(cell.getWall(i));
	}

	for(unsigned int i = 0; i < cell.getEffects().size(); i++){
		render(*(cell.getEffects()[i]));
	}

	if (cell.actorExists()){
		BoardActor& actor = *(cell.getActor());
		render(actor);
	}

}

void Renderer::render(const BoardStatic& piece){
	double size = piece.getCurrentAnimationFrame().getSize()/2.0;

	Coordinate2D<double> topLeft = piece.getScreenLocation();
	topLeft = ScreenCoordinate(topLeft.x, topLeft.y);
	Coordinate2D<double> botLeft(topLeft.x, topLeft.y+size);
	Coordinate2D<double> botRight(topLeft.x+size, topLeft.y+size);
	Coordinate2D<double> topRight(topLeft.x+size, topLeft.y);

	auto color = piece.getCurrentAnimationFrame().getColor();
	drawQuadrangle(botLeft, botRight, topLeft, topRight, color);
}

void Renderer::render(const BoardActor& actor){
	float size = actor.getCurrentAnimationFrame().getSize();

	Coordinate2D<double> topLeft = actor.getScreenLocation();
	Coordinate2D<double> botRight(topLeft.x+size, topLeft.y+size);

	drawQuadrangle_textured(topLeft, botRight,
			actor.getCurrentAnimationFrame().tex_topLeft, actor.getCurrentAnimationFrame().tex_botRight,
			actor.spriteSheet);
}

void Renderer::render(const Effect& effect){
	Coordinate2D<double> topLeft = effect.getScreenLocation();
	topLeft = Coordinate2D<double>(topLeft.x+0.0025, topLeft.y+0.0025);
	Coordinate2D<double> botLeft(topLeft.x, topLeft.y+0.005);
	Coordinate2D<double> botRight(topLeft.x+0.005, topLeft.y+0.005);
	Coordinate2D<double> topRight(topLeft.x+0.005, topLeft.y);

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
void Renderer::drawQuadrangle(const Coordinate2D<double> botLeft, const Coordinate2D<double> botRight,
							  const Coordinate2D<double> topLeft, const Coordinate2D<double> topRight,
							  const std::tuple<float, float, float> color) {
	glBindTexture(GL_TEXTURE_2D, 0);
	glColor3f(std::get<0>(color), std::get<1>(color), std::get<2>(color));

	glBegin(GL_QUADS);
	glVertex2f(botLeft.x, 1-botLeft.y);
	glVertex2f(botRight.x, 1-botRight.y);
	glVertex2f(topRight.x, 1-topRight.y);
	glVertex2f(topLeft.x, 1-topLeft.y);
	glEnd();
}

void Renderer::drawQuadrangle(const Coordinate2D<double>& topLeft, const Coordinate2D<double>& botRight,
		const std::tuple<float, float, float> color){

	glBindTexture(GL_TEXTURE_2D, 0);
	glColor3f(std::get<0>(color), std::get<1>(color), std::get<2>(color));

	glBegin(GL_QUADS);
	glVertex2f(topLeft.x, topLeft.y-1);
	glVertex2f(topLeft.x, botRight.y-1);
	glVertex2f(botRight.x, botRight.y-1);
	glVertex2f(botRight.x, topLeft.y-1);
	glEnd();

}


void Renderer::drawQuadrangle_textured(const Coordinate2D<double>& topLeft, const Coordinate2D<double>& botRight,
							  const Coordinate2D<double>& tex_topLeft, const Coordinate2D<double>& tex_botRight,
							  const GLuint& texture) {
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS);
	glTexCoord2f(tex_topLeft.x, tex_topLeft.y); 	 glVertex2f(topLeft.x, 1-topLeft.y);
	glTexCoord2f(tex_topLeft.x, tex_botRight.y);	 glVertex2f(topLeft.x, 1-botRight.y);
	glTexCoord2f(tex_botRight.x, tex_botRight.y); 	 glVertex2f(botRight.x, 1-botRight.y);
	glTexCoord2f(tex_botRight.x, tex_topLeft.y);	 glVertex2f(botRight.x, 1-topLeft.y);
	glEnd();
}

