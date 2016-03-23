#include "Renderer.h"


Renderer::Renderer(const GameModel &model, const GameView &view)
	: model(model), view(view)
{}


void Renderer::render(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	int dx, dy;
	const GameBoardStructure &board = model.getGameBoard().getBoard();
	Coordinate2D<int> startColumn = view.getRearColumn(board.getWidth(), board.getLength());
	Coordinate2D<int> traverseVector = view.getDiagonalTraversalVector();
	dx = traverseVector.x;
	dy = traverseVector.y;
	Coordinate3D<int> startCoord(startColumn.x, startColumn.y, 0);

	for (; board.inBounds(startCoord); startCoord.x -= dx)
	{
		renderBoardDiagonal(board, startCoord, dx, dy);
	}
	startCoord.x += dx;

	for(; board.inBounds(startCoord); startCoord.y += dy)
	{
		renderBoardDiagonal(board, startCoord, dx, dy);
	}

	glFlush();
}


void Renderer::renderBoardDiagonal(const GameBoardStructure& board, Coordinate3D<int> startCoord, int dx, int dy)
{
	for (; board.inBounds(startCoord); startCoord.x += dx, startCoord.y += dy)
	{
		renderBoardCoordinate(board, startCoord);
	}
}

void Renderer::renderBoardCoordinate(const GameBoardStructure& board, Coordinate3D<int> coord)
{
	Coordinate3D<double> lookAtCoordinate = view.getLookAtCoordinate();
	double x = lookAtCoordinate.x;
	double y = lookAtCoordinate.y;
	double zoom = view.getZoom();
	double spriteWidth = zoom * SPRITE_UNIT_WIDTH;
	double spriteHeight = zoom * SPRITE_UNIT_HEIGHT;
	double perspectiveDepth = zoom * PERSPECTIVE_DEPTH;
	// double perspectiveHeight = zoom * PERSPECTIVE_HEIGHT;

	Coordinate2D<double> originScrCoord;
	originScrCoord.x = .5 + (y - x)*spriteWidth/2;
	originScrCoord.y = .5 - perspectiveDepth * (x+y);

	int u = coord.x;
	int v = coord.y;

	Coordinate2D<double> scrCoord;
	scrCoord.x = originScrCoord.x + (u - v)*spriteWidth/2;
	scrCoord.y = originScrCoord.y + perspectiveDepth * (u+v);

	Coordinate2D<double> scrCoordBotRight;
	scrCoordBotRight.x = scrCoord.x + spriteWidth;
	scrCoordBotRight.y = scrCoord.y + spriteHeight;

	Coordinate2D<double> scrCoordTex1(0,0);
	Coordinate2D<double> scrCoordTex2(1,1);


	drawQuadrangle_textured(scrCoord, scrCoordBotRight, scrCoordTex1, scrCoordTex2, board.spriteSheet);
	if ((u+v)%5 == 0)
		drawQuadrangle_textured(scrCoord, scrCoordBotRight, scrCoordTex1, scrCoordTex2, board.spriteSheet2);
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
	render(cell.getFloor());

	for(int i = 0; i < 4; i++){
		render(cell.getWall((BoardWall::WallEdge)i));
	}

	for(unsigned int i = 0; i < cell.getNumEffects(); i++){
		render(cell.getEffect(i));
	}

	if (cell.actorExists()){
		render(cell.getActor());
	}

}

void Renderer::render(const BoardStatic& piece){
	double size = piece.getCurrentAnimationFrame().getSize()/2.0;

	Coordinate2D<double> topLeft = piece.getScreenLocation();
	topLeft = Coordinate2D<double>(topLeft.x, topLeft.y);
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
			actor.getSpriteSheet());
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
	glColor3f(255, 255, 255);

	glBegin(GL_QUADS);
	glTexCoord2f(tex_topLeft.x, tex_topLeft.y); 	 glVertex2f(topLeft.x, 1-topLeft.y);
	glTexCoord2f(tex_topLeft.x, tex_botRight.y);	 glVertex2f(topLeft.x, 1-botRight.y);
	glTexCoord2f(tex_botRight.x, tex_botRight.y); 	 glVertex2f(botRight.x, 1-botRight.y);
	glTexCoord2f(tex_botRight.x, tex_topLeft.y);	 glVertex2f(botRight.x, 1-topLeft.y);
	glEnd();
}

