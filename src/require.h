#ifndef REQUIRE_H
#define REQUIRE_H
	#define __USEGLAD__ 
	#include <stdlib.h>
	#include <stdio.h>
	#include <stdbool.h>

	#ifdef __USEGLAD__
		#include <KHR/khrplatform.h>
		#include <glad/glad.h>
	#else
		#include <GL/gl.h>
	#endif

	#ifdef __APPLE_
		#include <GLUT/glut.h>
	#else
		#include <GL/glut.h>
	#endif
	
	#include "core/mathematics.h"
	#include "core/colors.h"
	#include "core/time.h"
	#include "core/shaders.h"
	
	/*
		#include <lua.h>
		#include <lualib.h>
		#include <lauxlib.h>
	*/


#endif
