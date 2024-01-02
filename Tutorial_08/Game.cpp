#include "Game.h"

Game::Game()
{

	backgrounds = new Sprite("C:\\Users\\for-t\\Desktop\\openglTutorial\\Learn-Computer-Graphics\\resources\\bg.png", glm::vec2(300));
	backgrounds->scale(glm::vec2(1000));
	
}

Game::~Game()
{
}

void Game::input()
{
}

void Game::Draw(ShaderProgram* shader)
{
	shader->Send_Mat4("model_matrx", backgrounds->transformation());
	
	backgrounds->Draw();
	backgrounds->scale(glm::vec2(1000));

}
