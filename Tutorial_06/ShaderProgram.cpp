#include "ShaderProgram.h"
#include<glew.h>
#include<iostream>
using namespace std;




ShaderProgram::ShaderProgram(const char* vertex_shader, const char* fragment_shader)
{
	// compile shader

	unsigned int vertex,fragment;
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex,1,&vertex_shader,NULL);
	glCompileShader(vertex);
	checkerorr(vertex, "vertex");

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragment_shader, NULL);
	glCompileShader(fragment);
	checkerorr(fragment, "fragment");


	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);

	checkerorr(ID, "program");

	glDeleteShader(vertex);
	glDeleteShader(fragment);

}

ShaderProgram::~ShaderProgram()
{
	glDeleteShader(ID);
	
}

void ShaderProgram::use()
{
	glUseProgram(ID);
}

void ShaderProgram::Send_Mat4(const char* name, glm::mat4& mat)
{
	unsigned int location=glGetUniformLocation(ID,name);
	glUniformMatrix4fv(location, 1, GLU_FALSE,&mat[0][0]);
}

void ShaderProgram::checkerorr(unsigned int shader_id, std::string type)
{

	int scussess;
	char infolog[1024];
	if (type != "porgram") {
		glGetShaderiv(shader_id,GL_COMPILE_STATUS,&scussess);
	
		if (!scussess) {
			glGetShaderInfoLog(shader_id, 1024, NULL,infolog);
			std::cout << "Error type"<<type<<"\n";
			std::cout << "Error " << infolog << "\n" <<
				"============================== \n";
	}

		else
		{
			glGetProgramiv(shader_id, GL_LINK_STATUS, &scussess);
			if (!scussess) {
				glGetProgramInfoLog(shader_id, 1024,NULL,infolog);

				std::cout << "Error type" << type << "\n";
				std::cout << "Error " << infolog << "\n"<<
				"============================== \n";

			}
		}
	
	}
}
