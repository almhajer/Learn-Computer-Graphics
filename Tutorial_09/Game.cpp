#include "Game.h"

Game::Game()
{

	background = new Sprite("resources/bg.png", glm::vec2(0));

	
	background->scale(glm::vec2(400, 400));
}

Game::~Game()
{
}

void Game::input()
{
}

void Game::Draw(ShaderProgram* shader)
{

	shader->Send_Mat4("model_matrx", background->transformation());

	background->Draw();
}
