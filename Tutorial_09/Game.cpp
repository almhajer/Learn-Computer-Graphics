#include "Game.h"

Game::Game()
{

	bg = new Sprite("resources/bg.png", glm::vec2(0));

	bg->scale(glm::vec2(2000, 2000));
}

Game::~Game()
{
}

void Game::input()
{
}

void Game::Draw(ShaderProgram* shader)
{

	shader->Send_Mat4("model_matrx", bg->transformation());

	bg->Draw();
}
