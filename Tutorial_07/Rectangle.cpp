#include "Rectangle.h"
#include<glew.h>
#include"gtc/matrix_transform.hpp"
Rectangle::Rectangle():position(glm::vec2(0.0)),scale(glm::vec2(1)), rotation_angle(0.0f)
{
	glm::vec2 arr[6] = {
		glm::vec2(0,0),
		glm::vec2(0,1),
		glm::vec2(1,0),

		glm::vec2(1,0),
		glm::vec2(0,1),
		glm::vec2(1,1)

	};
	glm::vec4 colors[6]{
		glm::vec4(1,1,1,1.1),
		glm::vec4(1,1,1,1.1),
		glm::vec4(1,1,1,1.1),
		glm::vec4(1,1,1,1.1),
		glm::vec4(1,1,1,1.1),
		glm::vec4(1,1,1,1.1)

	};

	glm::vec2 uv[6] = {
		glm::vec2(0,0),
		glm::vec2(0,1),
		glm::vec2(1,0),

		glm::vec2(1,0),
		glm::vec2(0,1),
		glm::vec2(1,1)

	};


	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);


	glGenBuffers(1, &CBO);
	glGenBuffers(1, &UVBO);


	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(glm::vec2),&arr[0], GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, NULL);


	//COLOR
	glBindBuffer(GL_ARRAY_BUFFER, CBO);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(glm::vec4), &colors[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, false, 0, NULL);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	// uv picture

	glBindBuffer(GL_ARRAY_BUFFER, UVBO);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(glm::vec2), &uv[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, false, 0, NULL);
}

Rectangle::~Rectangle()
{
	glDeleteVertexArrays(1, &VAO);
	//glDeleteVertexArrays(1, &CBO);

	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &CBO);
	glDeleteBuffers(1, &UVBO);

}

void Rectangle::Draw()
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

glm::mat4 Rectangle::GetTransformtionMatrx()
{
	glm::mat4 translation = glm::translate(glm::mat4(1.0f), glm::vec3(position, 1.0));
	glm::mat4 Rotation = glm::rotate(glm::mat4(1.0f), rotation_angle, glm::vec3(0.0f, 0.0f,1.0));
	glm::mat4 scal = glm::scale(glm::mat4(1.0f), glm::vec3(scale, 1.0f));
	
	
	return translation *Rotation*scal ;
}

void Rectangle::setposition(glm::vec2 pos)
{
	position = pos;
}

void Rectangle::setscale(glm::vec2 scal)
{
	scale = scal;
}

void Rectangle::setrotation(float rotation)
{
	rotation_angle = rotation;
}

glm::vec2 Rectangle::getposition()
{
	return position;
}

glm::vec2 Rectangle::getscale()
{
	return scale;
}

float Rectangle::getrotation()
{
	return rotation_angle;
}
