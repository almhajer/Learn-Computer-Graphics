#include "Window.h"


int main() {
	Window* window;
	window= new Window(600, 800);
	window->MainLoop();


	return 0;
}