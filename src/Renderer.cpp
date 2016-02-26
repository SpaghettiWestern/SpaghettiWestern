#include "Renderer.h"


Renderer::Renderer(const GameModel &model, const GameView &view)
	: model(model), view(view)
{}


void Renderer::render(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	int dx, dy;
	const GameBoardStructure &board = model.getGameBoard().getBoard();
	Coordinate2D<int> startColumn = view.getRearColumn();
	Coordinate2D<int> traverseVector = view.getDiagonalTraversalVector();
	//dx = -1;
	//dy = 1;
	dx = traverseVector.x;
	dy = traverseVector.y;
	Coordinate startCoord(startColumn.x * board.getWidth(), startColumn.y * board.getLength());

	for (; board.inBounds(startCoord); startCoord.first -= dx)
	{
		renderBoardDiagonal(board, startCoord, dx, dy);
	}
	startCoord.first += dx;

	for(; board.inBounds(startCoord); startCoord.second += dy)
	{
		renderBoardDiagonal(board, startCoord, dx, dy);
	}

	glFlush();
}


void Renderer::renderBoardDiagonal(const GameBoardStructure& board, Coordinate startCoord, int dx, int dy)
{
	for (; board.inBounds(startCoord); startCoord.first += dx, startCoord.second += dy)
	{
		renderBoardCoordinate(board, startCoord);
	}
}

void Renderer::renderBoardCoordinate(const GameBoardStructure& board, Coordinate coord)
{
	Coordinate3D<double> lookAtCoordinate = view.getLookAtCoordinate();
	double x = lookAtCoordinate.x;
	double y = lookAtCoordinate.y;
	double zoom = view.getZoom();
	double spriteWidth = zoom * SPRITE_UNIT_WIDTH;
	double spriteHeight = zoom * SPRITE_UNIT_HEIGHT;
	double perspectiveDepth = zoom * PERSPECTIVE_DEPTH;
	// double perspectiveHeight = zoom * PERSPECTIVE_HEIGHT;

	ScreenCoordinate originScrCoord;
	originScrCoord.first = .5 + (y - x)*spriteWidth/2;
	originScrCoord.second = .5 - perspectiveDepth * (x+y);

	int u = coord.first;
	int v = coord.second;

	ScreenCoordinate scrCoord;
	scrCoord.first = originScrCoord.first + (u - v)*spriteWidth/2;
	scrCoord.second = originScrCoord.second + perspectiveDepth * (u+v);

	ScreenCoordinate scrCoordBotRight;
	scrCoordBotRight.first = scrCoord.first + spriteWidth;
	scrCoordBotRight.second = scrCoord.second + spriteHeight;

	ScreenCoordinate scrCoordTex1(0,0);
	ScreenCoordinate scrCoordTex2(1,1);

	drawQuadrangle_textured(scrCoord, scrCoordBotRight, scrCoordTex1, scrCoordTex2, board.spriteSheet);
}

void Renderer::render(const BoardStatic& piece){
	double size = piece.getCurrentAnimationFrame().getSize()/2.0;

	ScreenCoordinate topLeft = piece.getScreenLocation();
	topLeft = ScreenCoordinate(topLeft.first, topLeft.second);
	ScreenCoordinate botLeft(topLeft.first, topLeft.second+size);
	ScreenCoordinate botRight(topLeft.first+size, topLeft.second+size);
	ScreenCoordinate topRight(topLeft.first+size, topLeft.second);

	auto color = piece.getCurrentAnimationFrame().getColor();
	drawQuadrangle(botLeft, botRight, topLeft, topRight, color);
}

void Renderer::render(const BoardActor& actor){
	float size = actor.getCurrentAnimationFrame().getSize();

	ScreenCoordinate topLeft = actor.getScreenLocation();
	ScreenCoordinate botRight(topLeft.first+size, topLeft.second+size);

	drawQuadrangle_textured(topLeft, botRight,
			actor.getCurrentAnimationFrame().tex_topLeft, actor.getCurrentAnimationFrame().tex_botRight,
			actor.spriteSheet);
}

void Renderer::render(const Effect& effect){
	ScreenCoordinate topLeft = effect.getScreenLocation();
	topLeft = ScreenCoordinate(topLeft.first+0.0025, topLeft.second+0.0025);
	ScreenCoordinate botLeft(topLeft.first, topLeft.second+0.005);
	ScreenCoordinate botRight(topLeft.first+0.005, topLeft.second+0.005);
	ScreenCoordinate topRight(topLeft.first+0.005, topLeft.second);

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
	//glColor3f(std::get<0>(color), std::get<1>(color), std::get<2>(color));
	glColor3f(255, 255, 255); // draws every square white

	glBegin(GL_QUADS);
	glVertex2f(botLeft.first, 1-botLeft.second);
	glVertex2f(botRight.first, 1-botRight.second);
	glVertex2f(topRight.first, 1-topRight.second);
	glVertex2f(topLeft.first, 1-topLeft.second);
	glEnd();
}

void Renderer::drawQuadrangle(const ScreenCoordinate& topLeft, const ScreenCoordinate& botRight,
		const std::tuple<float, float, float> color){

	glBindTexture(GL_TEXTURE_2D, 0);
	glColor3f(std::get<0>(color), std::get<1>(color), std::get<2>(color));

	glBegin(GL_QUADS);
	glVertex2f(topLeft.first, topLeft.second-1);
	glVertex2f(topLeft.first, botRight.second-1);
	glVertex2f(botRight.first, botRight.second-1);
	glVertex2f(botRight.first, topLeft.second-1);
	glEnd();

}


void Renderer::drawQuadrangle_textured(const ScreenCoordinate& topLeft, const ScreenCoordinate& botRight,
							  const ScreenCoordinate& tex_topLeft, const ScreenCoordinate& tex_botRight,
							  const GLuint& texture) {
	glBindTexture(GL_TEXTURE_2D, texture);
	glColor3f(255, 255, 255);

	glBegin(GL_QUADS);
	glTexCoord2f(tex_topLeft.first, tex_topLeft.second); 	 glVertex2f(topLeft.first, 1-topLeft.second);
	glTexCoord2f(tex_topLeft.first, tex_botRight.second);	 glVertex2f(topLeft.first, 1-botRight.second);
	glTexCoord2f(tex_botRight.first, tex_botRight.second); 	 glVertex2f(botRight.first, 1-botRight.second);
	glTexCoord2f(tex_botRight.first, tex_topLeft.second);	 glVertex2f(botRight.first, 1-topLeft.second);
	glEnd();
}

