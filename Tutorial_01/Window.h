#pragma once
#include<glfw3.h>
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
};

