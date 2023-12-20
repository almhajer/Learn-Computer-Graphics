#include "Triangle.h"
#include<glew.h>
#include"gtc/matrix_transform.hpp"
Triangle::Triangle():position(glm::vec2(0.0)),scale(glm::vec2(1)), rotation_angle(0.0f)
{
	glm::vec2 arr[3] = {
		glm::vec2(0,0),
		glm::vec2(0,1),
		glm::vec2(1,0)
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);


	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(glm::vec2),&arr[0], GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

Triangle::~Triangle()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void Triangle::Draw()
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

glm::mat4 Triangle::GetTransformtionMatrx()
{
	glm::mat4 translation = glm::translate(glm::mat4(1.0f), glm::vec3(position, 1.0));
	glm::mat4 Rotation = glm::rotate(glm::mat4(1.0f), rotation_angle, glm::vec3(0.0f, 0.0f,1.0));
	glm::mat4 scal = glm::scale(glm::mat4(1.0f), glm::vec3(scale, 1.0f));
	
	
	return translation *Rotation*scal ;
}

void Triangle::setposition(glm::vec2 pos)
{
	position = pos;
}

void Triangle::setscale(glm::vec2 scal)
{
	scale = scal;
}

void Triangle::setrotation(float rotation)
{
	rotation_angle = rotation;
}
