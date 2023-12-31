#pragma once
#include<string>
#include"glm.hpp"
class ShaderProgram {

public:
	ShaderProgram(const char* vertex_shader,const char* fragment_shader);

	~ShaderProgram();
	void use();
	void Send_Mat4(const char* name,glm::mat4& mat);

private:
	void checkerorr(unsigned int shader_id, std::string type);
	unsigned int ID;
};