#include "WindowController.h"

WindowController::WindowController()
{
	window = nullptr;
}

WindowController::~WindowController()
{
	if (window != nullptr)
	{
		glfwTerminate();
		window = nullptr;
	}
}

void WindowController::NewWindow()
{
	M_ASSERT(glfwInit(), "Failed to initialize GLFW."); // Initialise GLFW

	// Open a window and create its OpenGL context
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	Resolution r = WindowController::GetResolution();
	M_ASSERT((window = glfwCreateWindow(r.width, r.height, "PROG3160", NULL, NULL)) != nullptr,
		"Failed to create GLFW window.");

	glfwMakeContextCurrent(window);
}

void WindowController::Create(int _width, int _height)
{
	if (_width == -1 || _height == -1)
	{
		const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		resolution = Resolution(mode->width, mode->height);
	}
	else
	{
		resolution = Resolution(_width, _height);
	}
}