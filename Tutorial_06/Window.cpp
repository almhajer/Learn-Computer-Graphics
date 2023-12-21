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

	window_ptr = glfwCreateWindow(width,height,"Tutorial_06",NULL,NULL);
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
			layout (location=1) in vec4 color;
			
			uniform mat4 projection;
			uniform mat4 model_matx;

			out vec4 vertex_color;

			void main(){

			gl_Position = projection*model_matx*vec4(position.x,position.y,0.0f,1.0f);
			vertex_color=color;
			}
		)CODE";

	const char* fs = R"CODE(
			#version 410 core
			out vec4 finalcolor;

			in vec4 vertex_color;

			void main(){
			finalcolor=vertex_color;
			}
		)CODE";




	camera = new Camera(m_width, m_height);
	shader = new ShaderProgram(vs, fs);




	//triangle

	triangle_renderer = new Rectangle();
	triangle_renderer->setposition(glm::vec2(200,250));
	triangle_renderer->setscale(glm::vec2(200, 200));
}

Window::~Window()
{
	delete camera;
	delete shader;

	delete triangle_renderer;
	glfwTerminate();
	
}

static glm::vec2 pos = glm::vec2(200,250);

void Window::Input()
{
	if (glfwGetKey(window_ptr,GLFW_KEY_ESCAPE)) {
		glfwSetWindowShouldClose(window_ptr,true);

	}

	if (glfwGetKey(window_ptr, GLFW_KEY_DELETE)) {
		
	//	points_renderer->Delete();
	}

	if (glfwGetKey(window_ptr, GLFW_KEY_UP)) {
		pos.y -= 1;
		triangle_renderer->setposition(pos);
	}
	if (glfwGetKey(window_ptr, GLFW_KEY_DOWN)) {
		pos.y += 1;
		triangle_renderer->setposition(pos);
	}

	if (glfwGetKey(window_ptr, GLFW_KEY_LEFT)) {
		pos.x -= 1;
		triangle_renderer->setposition(pos);
	}
	if (glfwGetKey(window_ptr, GLFW_KEY_RIGHT)) {
		pos.x += 1;
		triangle_renderer->setposition(pos);
	}


	//left click =0
	//right click =1
	//middle click =2
	if (glfwGetMouseButton(window_ptr,1)) {
		
		double x, y;
		glfwGetCursorPos(window_ptr, &x, &y);
		glm::vec2 mouse_position (x, y);

		//lines_renderer->Add(mouse_position);
	}



}
//float angle = 0;
void Window::MainLoop()
{
	while (!glfwWindowShouldClose(window_ptr))
	{
		Resize();
		Input();
		glClearColor(0.0f, 0.0f, 0.f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		
		//angle += 0.001f;
		//triangle_renderer->setrotation(angle);


		shader->Send_Mat4("projection", camera->Get_Projection());
		shader->Send_Mat4("model_matx", triangle_renderer->GetTransformtionMatrx());
		shader->use();
		/*points_renderer->Draw();
		lines_renderer->Draw();*/
		
		triangle_renderer->Draw();
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
