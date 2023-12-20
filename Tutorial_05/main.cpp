#include "Window.h"


int main() {
	Window* window;
	window= new Window(1200, 1200);
	window->MainLoop();


	return 0;
}