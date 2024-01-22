#include "Window.h"



using namespace std;


Window::Window(int width, int height) :m_width(width), m_height(height)
{
	glfwInit();
	// opengl 3.3 modern 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window_ptr = glfwCreateWindow(width, height, "Tutorial_09", NULL, NULL);
	if (window_ptr == nullptr) {
		std::cout << "not can make window \n";
	}
	glfwMakeContextCurrent(window_ptr);

	if (glewInit()) {
		std::cout << "can't initlize glew \n";
	}
	// add pointsd

	//تفعيل الشفافية
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	const char* vs = R"CODE(
			#version 330 core
			layout(location = 0) in vec2 position;
			layout(location = 1) in vec4 color;
			layout(location = 2) in vec2 uv;


			uniform mat4 projection;
			uniform mat4 model_matrx;

			out vec4 vertex_color;
			out vec2 vertex_uv;

			void main(){

			gl_Position = projection * model_matrx * vec4(position.x,position.y,0.0,1.0);
			vertex_color=color;
			vertex_uv=uv;
			}
		)CODE";

	const char* fs = R"CODE(
			#version 330 core
			out vec4 finalcolor;

			in vec4 vertex_color;
			in vec2 vertex_uv;
			
			uniform sampler2D sprite;

			void main(){
		finalcolor = vertex_color * texture(sprite,vertex_uv);
			}
		)CODE";




	camera = new Camera(m_width, m_height);
	shader = new ShaderProgram(vs, fs);
	game = new Game();

}

Window::~Window()
{
	delete camera;
	delete shader;
	delete game;
	glfwTerminate();

}



void Window::Input()
{
	if (glfwGetKey(window_ptr, GLFW_KEY_ESCAPE)) {
		glfwSetWindowShouldClose(window_ptr, true);

	}

	if (glfwGetKey(window_ptr, GLFW_KEY_DELETE)) {

		//	points_renderer->Delete();
	}

	if (glfwGetKey(window_ptr, GLFW_KEY_UP)) {
	
	}
	if (glfwGetKey(window_ptr, GLFW_KEY_DOWN)) {
	
	}

	if (glfwGetKey(window_ptr, GLFW_KEY_LEFT)) {
		
	}
	if (glfwGetKey(window_ptr, GLFW_KEY_RIGHT)) {
		
	}


	//left click =0
	//right click =1
	//middle click =2
	if (glfwGetMouseButton(window_ptr, 1)) {

		double x, y;
		glfwGetCursorPos(window_ptr, &x, &y);
		glm::vec2 mouse_position(x, y);

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


		shader->use();
		shader->Send_Mat4("projection", camera->Get_Projection());

		//الخلفية
		
			
		

		game->Draw(shader);

	

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
		glViewport(0, 0, width, height);
		printf("Resize to {Width %d }\t & {Height:%d} \n ", width, height);
		camera->Update_Viewport(m_width, m_height);
	}

}