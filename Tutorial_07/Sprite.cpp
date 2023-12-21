#include "Sprite.h"
#include"glm.hpp"
Sprite::Sprite(const char* imagepath, glm::vec2 position)
{
	texture = new Texture("C:\\Users\\for-t\\Desktop\\openglTutorial\\Learn-Computer-Graphics\\resources\\spaceship.png");
	rectangle = new Rectangle();
	rectangle->setposition(position);
	rectangle->setscale(glm::vec2(100,150));
}

Sprite::~Sprite()
{
	delete texture;
	delete rectangle;
}

void Sprite::Draw()

{
	texture->use();
	rectangle->Draw();
}

glm::mat4 Sprite::transformation()

{
	return rectangle->GetTransformtionMatrx();
}

void Sprite::move_up(float speed )
{
	glm::vec2 pos = rectangle->getposition();
	pos.y -=1 * speed;
	rectangle->setposition(pos);

}

void Sprite::move_left(float speed)
{
	glm::vec2 pos = rectangle->getposition();
	pos.x -= 1 * speed;
	rectangle->setposition(pos);
}

void Sprite::move_right(float speed)
{
	glm::vec2 pos = rectangle->getposition();
	pos.x += 1 * speed;
	rectangle->setposition(pos);
}

void Sprite::move_down(float speed)
{
	glm::vec2 pos = rectangle->getposition();
	pos.y += 1*speed;
	rectangle->setposition(pos);
}
