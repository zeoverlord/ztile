// Copyright 2013 Peter Wallström
//
// Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software distributed under the License is
// distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and limitations under the License.

// while it is not required i like to request a few things
// 1. please do share any meaningfull/usefull changes/additions/fixes you make with me so that i could include it in any future version
// 2. likewise do share any ideas for improvements
// 3. If you make something comersiol or at least something you release publicly that relies on this code then i would like to know and maybe use in my CV
// 4. Please do include me in your credits

// glz basecode - lets just say you will need this
// visit http://www.flashbang.se or contact me at overlord@flashbang.se
// the entire toolkit should exist in it's entirety at github
// https://github.com/zeoverlord/glz.git

#pragma once

#include "resource.h"

// these settings define how the application starts up and behaves

const wchar_t  WINDOW_TITLE[] = L"ZeoBase GL Framework";// what name you want windows to call it, dont touch the weird L in front of it since it's unicode
const bool  DISPLAY_ERRORS = false;						// set to false if you want to suppress errors
const bool  SHOW_FRAME = true;							// i normally dont but usefull if you want to make a more normal app
const bool  ALLOW_MAAXIMIZE = true;						// adds minimize/maximize buttons again usefull for a normal app
const bool  START_WINDOWED = true;						// starts in windowed mode instead of fullscreen
const bool  ALLOW_FULLSCREENSWITCH = false;				// doesn't work that well when showing a frame, infact dont even bother and set SHOW_FRAME to false
const bool  ALLOW_RESIZE = true;						// allows you to resice the window by dragging the borders, but only if SHOW_FRAME is true
const bool  START_CENTERED = true;						// centers the window which looks good IMHO
const unsigned int WINDOW_WIDTH	= 1280;
const unsigned int  WINDOW_HEIGHT =	720;
const unsigned int  FULLSCREEN_WIDTH = 1920;
const unsigned int  FULLSCREEN_HEIGHT = 1080;
const bool  NATIVE_FULLSCREEN = true;					// generally speaking this should be set to true, most often the current resolution is the higest anyway, overides the above settigns
const unsigned int  WINDOW_X = 0;
const unsigned int  WINDOW_Y = 0;
const bool  FORCE_OPENGL_VERSION = true;				// if you want to force openGL to a specific openGL version, generally set this to false for release, but for development it could be good to set it to true
const bool ENABLE_VSYNC = true;							// makes everything run a bit smoother, but at a constant rate, makes it impossible to get the current framerate

// Todo : change these to constants instead
// Todo #2 : change these to be loaded from a file instead
// Todo #3 : take over the world





typedef struct {									// Structure For Keyboard Stuff
	bool keyDown[256];								// Holds TRUE / FALSE For Each Key
	bool LMdown;
	bool RMdown;
	bool MMdown;
	int Mpos_x;
	int Mpos_y;
	int Mweel;
	bool Mactive;
} Keys;												// Keys

typedef struct {									// Contains Information Vital To Applications
	HINSTANCE		hInstance;						// Application Instance
	LPCWSTR		className;						// Application ClassName
} Application;										// Application

typedef struct {									// Window Creation Info
	Application*		application;				// Application Structure
	LPCWSTR				title;						// Window Title
	int					width;						// Width
	int					height;						// Height
	int					bitsPerPixel;				// Bits Per Pixel
	bool				isFullScreen;				// FullScreen?
} GL_WindowInit;									// GL_WindowInit

typedef struct {									// Contains Information Vital To A Window
	Keys*				keys;						// Key Structure
	HWND				hWnd;						// Window Handle
	HDC					hDC;						// Device Context
	HGLRC				hRC;						// Rendering Context
	GL_WindowInit		init;						// Window Init
	BOOL				isVisible;					// Window Visible?
	DWORD				lastTickCount;				// Tick Counter
	float				deltaTime;					// deltatime
	int					x,y;
} GL_Window;										// GL_Window

void TerminateApplication (GL_Window* window);		// Terminate The Application

void ToggleFullscreen (GL_Window* window);			// Toggle Fullscreen / Windowed Mode

BOOL Initialize (GL_Window* window, Keys* keys);	// Performs All Your Initialization

void Deinitialize (void);							// Performs All Your DeInitialization

void Update (float seconds);					// Perform Motion Updates

void Draw (void);									// Perform All Your Scene Drawing