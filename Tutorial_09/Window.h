#pragma once
#include<glfw3.h>
#include"Camera.h"
#include"Game.h"
class Window
{
public:

	Window(int width,int height);
	~Window();

	void Input();


	void MainLoop();


	void Resize();

private:
	int m_width, m_height;
	GLFWwindow* window_ptr;

	ShaderProgram* shader;

	Camera* camera;
	Sprite* spaceship;
	Sprite* bg;
	Game* bg_Game;
	
};

