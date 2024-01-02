#pragma once
#include "Sprite.h"
#include "ShaderProgram.h"
class Game
{
public:
	Game();
	~Game();
	void input();
	void Draw(ShaderProgram* shader);


private:
	Sprite* background;
	
};
