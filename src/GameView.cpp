#include "GameView.h"



GameView::GameView(GameModel& model) : model(model), renderer(Renderer(model)){

}

void GameView::render(){
	model.update();
	renderer.render();
}
