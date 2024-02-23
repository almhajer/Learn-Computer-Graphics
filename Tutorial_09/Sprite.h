#pragma once
#include"glm.hpp"
#include"Rectangle.h"
#include"Texture.h"


class Sprite {

public:
	Sprite(const char* imagepath, glm::vec2 position);
	~Sprite();

	void Draw();

	glm::mat4  transformation();

	void move_up(float speed=1);
	void move_left(float speed =1);
	void move_right(float speed =1 );
	void move_down(float speed = 1);

	void scale(glm::vec2 _scale);

	glm::vec2 getpostions();


private:
	Texture* texture;
	Rectangle* rectangle;
};