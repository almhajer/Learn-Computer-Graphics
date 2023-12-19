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

	window_ptr = glfwCreateWindow(width,height,"Tutorial_03",NULL,NULL);
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
			uniform mat4 projection;
			void main(){

			gl_Position = projection*vec4(position.x,position.y,0.0f,1.0f);

			}
		)CODE";

	const char* fs = R"CODE(
			#version 410 core
			out vec4 finalcolor;


			void main(){
			finalcolor=vec4(1,0,0,1);
			}
		)CODE";




	camera = new Camera(m_width, m_height);
	shader = new ShaderProgram(vs, fs);

	points_renderer = new Points();
	points_renderer->Add(glm::vec2(10, 10));
	points_renderer->Add(glm::vec2(100, 100));
	points_renderer->Add(glm::vec2(155, 150));

}

Window::~Window()
{
	delete points_renderer;
	delete camera;
	delete shader;
	glfwTerminate();
	
}

void Window::Input()
{
	if (glfwGetKey(window_ptr,GLFW_KEY_ESCAPE)) {
		glfwSetWindowShouldClose(window_ptr,true);

	}

	if (glfwGetKey(window_ptr, GLFW_KEY_DELETE)) {
		points_renderer->Delete();
	}
	//left click =0
	//right click =1
	//middle click =2
	if (glfwGetMouseButton(window_ptr,1)) {
		
		double x, y;
		glfwGetCursorPos(window_ptr, &x, &y);
		glm::vec2 mouse_position (x, y);

		points_renderer->Add(mouse_position);
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
		shader->Send_Mat4("projection", camera->Get_Projection());
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
		camera->Update_Viewport(width, height);
	}
	
}
