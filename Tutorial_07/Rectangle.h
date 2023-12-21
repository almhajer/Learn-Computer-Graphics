#pragma once
#include"glm.hpp"

class Rectangle {

public:
	Rectangle();
	~Rectangle();
	void Draw();

	glm::mat4 GetTransformtionMatrx();
	void setposition(glm::vec2 pos);
	void setscale(glm::vec2 scal);
	void setrotation(float rotation);


	glm::vec2 getposition();
	glm::vec2 getscale();
	float getrotation();


private:


	//vertex array object
	unsigned int VAO;
	// vertex buffer object
	unsigned int VBO;
	unsigned int CBO;
	unsigned int UVBO;


	// position

	glm::vec2 position;
	glm::vec2 scale;
	float  rotation_angle;
};