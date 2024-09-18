
#ifndef WINDOW_CONTROLLER_H
#define WINDOW_CONTROLLER_H

#include "StandardInclude.h"

class WindowController : public Singleton<WindowController>
{
public:
	//Constructoor / Destructors
	WindowController();
	virtual ~WindowController();

	// Accessors
	GLFWwindow* GetWindow() { if (window == nullptr) { NewWindow(); } return window; }

	// Methods
	void NewWindow();

private:
	// Members
	GLFWwindow* window;
};

#endif // ! WINDOW_CONTROLLER_H


