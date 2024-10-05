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
	M_ASSERT(glfwInit(), "Failed to initialize GLFW.");

	/*glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	M_ASSERT((window = glfwCreateWindow(1024, 768, "A sample scene", NULL, NULL)) != nullptr, "Failed to openGLFW window.");
	glfwMakeContextCurrent(window);


}

Resolution WindowController::GetResolution()
{
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	return Resolution(mode->width, mode->height, 45.0f);
}*/

	

	// Get the primary monitor and its video mode
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);

	// Create a window with the dimensions of the monitor
	window = glfwCreateWindow(mode->width, mode->height, "OpenGL Scene", monitor, NULL);
	M_ASSERT(window != nullptr, "Failed to create GLFW window.");

	glfwMakeContextCurrent(window);
}

Resolution WindowController::GetResolution() {
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	return Resolution(mode->width, mode->height, 45.0f);
}