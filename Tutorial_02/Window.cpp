#include<glew.h>
#include "Window.h"
#include<iostream>
using namespace std;



Window::Window(int width, int height):m_width(width),m_height(height)
{
	glfwInit();
	// opengl 3.3 modern 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

	window_ptr = glfwCreateWindow(width,height,"Tutorial_02",NULL,NULL);
	if (window_ptr ==nullptr) {
		std::cout << "not can make window \n";
	}
	glfwMakeContextCurrent(window_ptr);

	if (glewInit()) {
		std::cout << "can't initlize glew \n";
	}
	// add pointsd

	const char*vs=R"CODE(
			#version 410 core
			layout (location=0) in vec2 position;
			void main(){

			gl_Position = vec4(position.x,position.y,0.0f,1.0f);

			}
		)CODE";

	const char* fs = R"CODE(
			#version 410 core
			out vec4 finalcolor;


			void main(){
			finalcolor=vec4(1,0,0,1);
			}
		)CODE";





	shader = new ShaderProgram(vs, fs);

	points_renderer = new Points();
	points_renderer->Add(glm::vec2(0, 0));
	points_renderer->Add(glm::vec2(0.5, 0));
	points_renderer->Add(glm::vec2(0.5, 0.5));

}

Window::~Window()
{
	glfwTerminate();
	delete points_renderer;
}

void Window::Input()
{
	if (glfwGetKey(window_ptr,GLFW_KEY_ESCAPE)) {
		glfwSetWindowShouldClose(window_ptr,true);

	}
}

void Window::MainLoop()
{
	while (!glfwWindowShouldClose(window_ptr))
	{
		Resize();
		Input();
		glClearColor(0.5f, 0.8f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader->use();
		points_renderer->Draw();

		glfwSwapBuffers(window_ptr);
		glfwPollEvents();

	}
}

void Window::Resize()
{
	int width, height;
	glfwGetWindowSize(window_ptr, &width, &height);
	if (width != m_width || height != m_height) {
		m_height = height;
		m_width = width;
		glViewport(0,0,width, height);
		printf("Resize to {Width %d }\t & {Height:%d} \n ",width,height);
	}
	;
}
