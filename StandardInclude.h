#pragma once

#ifndef STANDARD_INCLUDE_H
#define STANDARD_INCLUDE_H

#define GLM_ENABLE_EXPERIMANTAL

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#ifdef  _WIN32
#include <Windows.h>
#define M_ASSERT(_cond, _msg) \
	if (!(_cond)) { OutputDebugStringA(_msg); std::abort(); glfwTerminate(); }
#endif

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include  <glm/glm.hpp>
#include <glm/ext.hpp>

#include "Singleton.h"

using namespace std;

#endif // !STANDARD_INCLUDE_H
