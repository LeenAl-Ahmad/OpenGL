#pragma once

#ifndef STANDARD_INCLUDE_H
#define STANDARD_INCLUDE_H

#include <vector>
#include <string>
#include <fstream>

#ifdef  _WIN32
#include <Windows.h>
#define M_ASSERT(_cond, _msg) \
	if (!(_cond)) { OutputDebugStringA(_msg); std::abort(); glfwTerminate(); }
#endif

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include  <glm/glm.hpp>

#include "Singleton.h"

#endif // !STANDARD_INCLUDE_H
