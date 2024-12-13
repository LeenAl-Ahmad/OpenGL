#pragma once

#ifndef STANDARD_INCLUDE_H
#define STANDARD_INCLUDE_H
#define TOOL_WINDOW_ENABLED
#define GLM_ENABLE_EXPERIMANTAL

#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

#ifdef  _WIN32
#include <Windows.h>
#define M_ASSERT(_cond, _msg) \
	if (!(_cond)) { OutputDebugStringA(_msg); std::abort(); glfwTerminate(); }
#endif
//font 
#include <ft2build.h>
#include FT_FREETYPE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Resolution.h"
#include "Singleton.h"

using namespace std;

#endif // !STANDARD_INCLUDE_H