/******************************************************************************
 *
 * @file	NelsonEngine.h
 *
 * @author	Lincoln Scheer
 * @since	02/21/2022
 *
 * @breif	NelsonEngine.h is a static header-only collection of the headers
 *          that Nelson requires. Grouping of includes in this file will allow
 *          an easy transition to using pre-compiled headers.
 *
 *****************************************************************************/

#ifndef NELSON_ENGINE_H
#define NELSON_ENGINE_H

// Standard Library
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

// SOIL2
#include "../vendor/SOIL2/SOIL2.h"

// OpenGL
#include <GL/glew.h>
#define GLEW_STATIC

// GLFW
#include <GLFW/glfw3.h>

// OpenGL Math Library
#include "../vendor/glm/glm.hpp"
#include "../vendor/glm/gtc/matrix_transform.hpp"
#include "../vendor/glm/gtc/type_ptr.hpp"

// Utilities
#include "Shader.h"
#include "TextureLoader.h"
#include "Window.h"

// Scene
#include "Scene.h"

#endif /* NELSON_ENGINE_H */