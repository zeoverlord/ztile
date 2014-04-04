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

// glz 2D example app - i wouldn't say it produces any meningfull results, but it's a start.
// visit http://www.flashbang.se or contact me at overlord@flashbang.se
// the entire toolkit should exist in it's entirety at github
// https://github.com/zeoverlord/glz.git



#include <windows.h>											// Header File For Windows
#include <gl\gl.h>												// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include <gl\glext.h>
#include "zeobase2.h"
#include <fstream>
#include <math.h>
#include "..\glz\ztool-geo.h"
#include "..\glz\ztool-shader.h"
#include "..\glz\ztool-glz.h"
#include "..\glz\ztool-vectormath.h"
#include "..\glz\ztool-tex.h"
#include "..\glz\ztool-geo-2d.h"
#include "..\glz\ztool-geo-generate.h"

using namespace std;										

#pragma comment( lib, "opengl32.lib" )							// Search For OpenGL32.lib While Linking
#pragma comment( lib, "glu32.lib" )								// Search For GLu32.lib While Linking

#ifndef CDS_FULLSCREEN											// CDS_FULLSCREEN Is Not Defined By Some
#define CDS_FULLSCREEN 4										// Compilers. By Defining It This Way,
#endif															// We Can Avoid Errors


GL_Window*	g_window;
Keys*		g_keys;

// User Defined Variables
float		angle=0,width,height;												// Used To Rotate The Triangles
unsigned int vao[16],vao_num[16],textvao[16],textvao_num[16];
glzMatrix m;
unsigned int texture[5],fonttexture[15];


char tbuffer[160];
char tbuffer2[160];
float texttimer=0;
float spriteframetimer=0;
int spriteframe=0;

int gamestate=1;

float paintarea_x = WINDOW_WIDTH / 2, paintarea_y = WINDOW_HEIGHT / 2, paintarea_Zoom = 512;

GLhandleARB  ProgramObject,ProgramObjectFT,ProgramObjectFSQ;
texture_transform text_tt;


int Mpos_x_old;
int Mpos_y_old;
int Mpos_x_rel;
int Mpos_y_rel;
int Mweel_old;
int Mweel_rel;


glzSimpleParticleSystem ps;

static PFNGLUSEPROGRAMPROC						glUseProgram;
static PFNGLUNIFORM1IPROC                       glUniform1i;
static PFNGLUNIFORMMATRIX4FVPROC                glUniformMatrix4fv;
static PFNGLUNIFORM4FARBPROC                    glUniform4f;
static PFNGLGETUNIFORMLOCATIONPROC              glGetUniformLocation;
static PFNGLBLENDCOLORPROC						glBlendColor;


#define COL_BLACK	0
#define COL_WHITE	1
#define COL_RED		2
#define COL_GREEN	3
#define COL_BLUE	4



BOOL Initialize (GL_Window* window, Keys* keys)					// Any GL Init Code & User Initialiazation Goes Here
{
	g_window	= window;
	g_keys		= keys;

	GetFocus();
	GetAsyncKeyState(WM_KEYUP);

	// Start Of User Initialization
	angle		= 0.0f;											// Set Starting Angle To Zero

	glClearColor (0.5f, 0.5f, 0.5f, 0.5f);						// Black Background
	glClearDepth (1.0f);										// Depth Buffer Setup
	glDepthFunc (GL_LEQUAL);									// The Type Of Depth Testing (Less Or Equal)
	glEnable (GL_DEPTH_TEST);									// Enable Depth Testing
	glShadeModel (GL_SMOOTH);									// Select Smooth Shading
	glHint (GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);			// Set Perspective Calculations To Most Accurate

	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	glFrontFace(GL_CCW);



	glUseProgram				= (PFNGLUSEPROGRAMPROC) wglGetProcAddress("glUseProgram");
	glGetUniformLocation		= (PFNGLGETUNIFORMLOCATIONPROC) wglGetProcAddress("glGetUniformLocation");                                                                     
	glUniform1i= (PFNGLUNIFORM1IPROC) wglGetProcAddress("glUniform1i");
	glUniform4f= (PFNGLUNIFORM4FARBPROC) wglGetProcAddress("glUniform4fARB");
	glUniformMatrix4fv= (PFNGLUNIFORMMATRIX4FVPROC) wglGetProcAddress("glUniformMatrix4fv");

	glBlendColor = (PFNGLBLENDCOLORPROC)wglGetProcAddress("glBlendColor");

	




	glzMatrix mt;
	mt.LoadIdentity();
	mt.scale(0.17f,0.17f,0.17f);

	ProgramObject = glzShaderLoad("data\\glsl.vert", "data\\glsl.frag", glzVAOType::AUTO);
//	ProgramObjectFT = glzShaderLoad("data\\fancytext.vert", "data\\fancytext.frag", glzVAOType::AUTO);
//	ProgramObjectFSQ = glzShaderLoad("data\\fsq.vert", "data\\fsq.frag", glzVAOType::AUTO);
	glzShaderLink(ProgramObject);
//	glzShaderLink(ProgramObjectFT);
//	glzShaderLink(ProgramObjectFSQ);
	// load the textures
	fonttexture[0] = glzLoadTexture("data\\fonts\\arial.tga", glzTexFilter::LINEAR);
//	fonttexture[1] = glzLoadTexture("data\\fonts\\minya_m.tga", glzTexFilter::LINEAR);
//	fonttexture[2] = glzLoadTexture("data\\fonts\\ms_gothic.tga", glzTexFilter::LINEAR);
	//fonttexture[3] = glzLoadTexture("data\\fonts\\digitalstrip_l.tga", glzTexFilter::LINEAR);
	//fonttexture[4] = glzLoadTexture("data\\fonts\\morpheus_l.tga", glzTexFilter::LINEAR);

//	texture[0] = glzLoadTexture("data\\back.tga", glzTexFilter::LINEAR);
//	texture[1] = glzLoadTexture("data\\derpy_phirana.tga", glzTexFilter::LINEAR);  // the derpy phirana is not an actual logo but just an example on how you can put it there
//	texture[2] = glzLoadTexture("data\\explotion128a.tga", glzTexFilter::NEAREST);
	texture[0] = glzLoadTexture("data\\tinytiles.tga", glzTexFilter::NEAREST);

	


	return TRUE;												// Return TRUE (Initialization Successful)
}


void Deinitialize (void)										// Any User DeInitialization Goes Here
{

	// this shouldn't normally be nessecary, but it's better to make it a habit to delete data for when you start to load and unload resources mid game.

	glzKillAllVAO();		// deletes all vaos in existance


}

void Update (float seconds)								// Perform Motion Updates Here
{


	Mweel_rel = g_keys->Mweel -Mweel_old;
	Mpos_x_rel = g_keys->Mpos_x - Mpos_x_old;
	Mpos_y_rel = g_keys->Mpos_y - Mpos_y_old;


		glzMatrix mt;
		mt.LoadIdentity();
		mt.scale(0.17f,0.17f,0.17f);


	if (g_keys->keyDown [VK_ESCAPE] == TRUE)					// Is ESC Being Pressed?
	{
		TerminateApplication (g_window);						// Terminate The Program
	}

	if (g_keys->keyDown [VK_F1] == TRUE)						// Is F1 Being Pressed?
	{
		ToggleFullscreen (g_window);							// Toggle Fullscreen Mode
	}

	if (gamestate==1)
	{
		angle += seconds;						// Update angle Based On The Clock
		if (angle>90001) angle=0;


	}

		if (g_keys->keyDown[VK_UP] == TRUE) paintarea_y += seconds * 150;
		if (g_keys->keyDown[VK_DOWN] == TRUE) paintarea_y -= seconds * 150;

		if (g_keys->keyDown[VK_LEFT] == TRUE) paintarea_x -= seconds * 150;
		if (g_keys->keyDown[VK_RIGHT] == TRUE) paintarea_x += seconds * 150;

		if (g_keys->keyDown[VK_SUBTRACT] == TRUE) paintarea_Zoom -= seconds * 150;
		if (g_keys->keyDown[VK_ADD] == TRUE) paintarea_Zoom += seconds * 150;


		// Todo: add if cursor points at tile surface
		//if (g_keys->keyDown[VK_SPACE] == TRUE)
		//{
			if (g_keys->RMdown == TRUE) 
			{
				paintarea_x += Mpos_x_rel;
				paintarea_y -= Mpos_y_rel;
			}
		//}

		paintarea_Zoom += Mweel_rel;
		if (paintarea_Zoom < 120) paintarea_Zoom = 120;
	

	if (g_keys->keyDown['1'] == TRUE) gamestate = 1;



	Mweel_old = g_keys->Mweel;
	Mpos_x_old = g_keys->Mpos_x;
	Mpos_y_old = g_keys->Mpos_y;

}


void draw_text(float x, float y, int text, int font, unsigned int po, unsigned int col)
{
	glUseProgram(po);

	unsigned int loc1 = glGetUniformLocation(po,"projMat");
	unsigned int loc2 = glGetUniformLocation(po,"texunit0");
	unsigned int loc3 = glGetUniformLocation(po,"tint");
	m.LoadIdentity();
	m.ortho( -4, 4, -2, 2, -100, 100);
	m.translate(x,y,0);

	float mtemp[16];
	m.transferMatrix(&mtemp[0]);
	glUniformMatrix4fv(loc1, 1, GL_FALSE, mtemp);

	if (col==COL_BLACK)	glUniform4f(loc3, 0.0f,0.0f,0.0f,1.0f);
	if (col==COL_WHITE)	glUniform4f(loc3, 1.0f,1.0f,1.0f,1.0f);
	if (col==COL_RED)	glUniform4f(loc3, 1.0f,0.0f,0.0f,1.0f);
	if (col==COL_GREEN)	glUniform4f(loc3, 0.0f,1.0f,0.0f,1.0f);
	if (col==COL_BLUE)	glUniform4f(loc3, 0.0f,0.0f,1.0f,1.0f);


	

	glBindTexture(GL_TEXTURE_2D,fonttexture[font]);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glzDrawVAO(textvao_num[text],textvao[text],GL_TRIANGLES);
	glDisable(GL_BLEND);

}

void draw_text2(char text[255], float x, float y, float scale, float kern, int font, unsigned int po, unsigned int col)
{
	glUseProgram(po);

	unsigned int loc1 = glGetUniformLocation(po, "projMat");
	unsigned int loc2 = glGetUniformLocation(po, "texunit0");
	unsigned int loc3 = glGetUniformLocation(po, "tint");
	m.LoadIdentity();
	m.ortho2DPixelspace( WINDOW_HEIGHT, WINDOW_WIDTH, glzOrigin::BOTTOM_LEFT);	
	m.translate(x, y, 0);

	float mtemp[16];
	m.transferMatrix(&mtemp[0]);
	glUniformMatrix4fv(loc1, 1, GL_FALSE, mtemp);

	if (col == COL_BLACK)	glUniform4f(loc3, 0.0f, 0.0f, 0.0f, 1.0f);
	if (col == COL_WHITE)	glUniform4f(loc3, 1.0f, 1.0f, 1.0f, 1.0f);
	if (col == COL_RED)	glUniform4f(loc3, 1.0f, 0.0f, 0.0f, 1.0f);
	if (col == COL_GREEN)	glUniform4f(loc3, 0.0f, 1.0f, 0.0f, 1.0f);
	if (col == COL_BLUE)	glUniform4f(loc3, 0.0f, 0.0f, 1.0f, 1.0f);

	float aspect = (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT;

	glDisable(GL_DEPTH_TEST);
	glBindTexture(GL_TEXTURE_2D, fonttexture[font]);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glzDirectDrawText(text, scale, aspect, kern, glzOrigin::BOTTOM_LEFT);
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);

}



// custom sprite rendering function, if you have a lot of sprites then one of these is probably usefull
void draw_sprite(float x, float y, float s, int sprite, int tx, int offset, unsigned int po, float col[4])
{
	glUseProgram(po);

	unsigned int loc1 = glGetUniformLocation(po,"projMat");
	unsigned int loc2 = glGetUniformLocation(po,"texunit0");
	unsigned int loc3 = glGetUniformLocation(po,"tint");
	m.LoadIdentity();
	m.ortho(-4, 4, -2, 2, -100, 100);
	m.translate(x,y,0);
	m.scale(s,s,s);

	float mtemp[16];
	m.transferMatrix(&mtemp[0]);
	glUniformMatrix4fv(loc1, 1, GL_FALSE, mtemp);

	glUniform4f(loc3, col[0],col[1],col[2],col[3]);

	glBindTexture(GL_TEXTURE_2D,texture[tx]);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glzDrawVAO(offset*6,6,vao[sprite],GL_TRIANGLES);
	glDisable(GL_BLEND);

}

// backdrops are usefull, if you don't have the time to write a 2D renderer then just cheat with a texture backdrop instead
void draw_backdrop(unsigned int bgtexture)
{
	glUseProgram(ProgramObjectFSQ);
	unsigned int loc1 = glGetUniformLocation(ProgramObjectFSQ,"projMat");
	unsigned int loc2 = glGetUniformLocation(ProgramObjectFSQ,"texunit0");
	unsigned int loc3 = glGetUniformLocation(ProgramObjectFSQ,"tint");
	
	m.LoadIdentity();

	float mtemp[16];
	m.transferMatrix(&mtemp[0]);
	glUniformMatrix4fv(loc1, 1, GL_FALSE, mtemp);
	glUniform1i(loc2, 0);
	glUniform4f(loc3, 1.0f,1.0f,1.0f,1.0f);
	glBindTexture(GL_TEXTURE_2D,bgtexture);
	glzDrawVAO(vao_num[0],vao[0],GL_TRIANGLES);

}

void draw_backdrop2(unsigned int bgtexture, glzMatrix mat, float col[4])
{
	glUseProgram(ProgramObjectFSQ);
	unsigned int loc1 = glGetUniformLocation(ProgramObjectFSQ,"projMat");
	unsigned int loc2 = glGetUniformLocation(ProgramObjectFSQ,"texunit0");
	unsigned int loc3 = glGetUniformLocation(ProgramObjectFSQ,"tint");
	


	float mtemp[16];
	mat.transferMatrix(&mtemp[0]);
	glUniformMatrix4fv(loc1, 1, GL_FALSE, mtemp);

	glUniform1i(loc2, 0);
	glUniform4f(loc3, col[0],col[1],col[2],col[3]);
	glBindTexture(GL_TEXTURE_2D,bgtexture);
	glzDrawVAO(vao_num[0],vao[0],GL_TRIANGLES);

}


void Draw (void)
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear Screen And Depth Buffer
	
	float mtemp[16];
	glEnable(GL_TEXTURE_2D);
	unsigned int loc1 = glGetUniformLocation(ProgramObject,"projMat");
	unsigned int loc2 = glGetUniformLocation(ProgramObject,"texunit0");
	unsigned int loc3 = glGetUniformLocation(ProgramObject,"tint");

//	unsigned int loc4 = glGetUniformLocation(ProgramObjectFT,"projMat");
//	unsigned int loc5 = glGetUniformLocation(ProgramObjectFT,"texunit0");

	glUseProgram(ProgramObject);
	glUniform1i(loc2, 0);	
	glUniform4f(loc3, 1.0f,1.0f,1.0f,1.0f);

	// i have used these gamestates in a few games for LD48 now and they are really quick and dirty, but effective.
	// they allow you to quickly make a title screen and end screen at the end of the project without changing that much code, instead you just encapsulate it in a gamestate


	if (gamestate == 1)
	{

		m.LoadIdentity();
		m.ortho(-400, 400, -250, 250, -100, 100);


	//	m.transferMatrix(&mtemp[0]);
	//	glUniformMatrix4fv(loc1, 1, GL_FALSE, mtemp);

		//glBindTexture(GL_TEXTURE_2D, texture[1]);
	
	//	glzDirectSpriteRender(m, texture[1], 0, 0, 2, 100, 100, 0, 0, 1.0, 1.0, glzOrigin::CENTERED);
	//	glzDirectSpriteRender(m, texture[1], 0, 0, 2, 100, 100, 0, 0, 1.0, 1.0, glzOrigin::BOTTOM_LEFT);
		
	//	glzDirectSpriteRender(m, texture[1], 0, 0, 2, 100, 100, 0, 0, 1.0, 1.0, glzOrigin::BOTTOM_RIGHT);
		//glzDirectSpriteRender(m, texture[1], 0, 0, 2, 100, 100, 0, 0, 1.0, 1.0, glzOrigin::TOP_RIGHT);

	//	glBlendFunc(GL_ONE, GL_ONE);
		//glBlendFunc(GL_CONSTANT_COLOR, GL_ONE_MINUS_CONSTANT_COLOR);
		//glBlendColor(1, 0, 1, 1.0f);
	//	glEnable(GL_BLEND);

	//	glzDrawTexture(texture[0], 0, 0, 0, 200, 200, 3, 0, 0, 1, 1);

		glzDrawTexture(texture[0], 0, paintarea_x - (paintarea_Zoom*0.5), paintarea_y - (paintarea_Zoom*0.5), paintarea_x + (paintarea_Zoom*0.5), paintarea_y + (paintarea_Zoom*0.5), 3, 0, 0, 1, 1);

		glDisable(GL_BLEND);

		//glBindTexture(GL_TEXTURE_2D, texture[3]);

	//	glUniform4f(loc3, 1.0f, 0.0f, 1.0f, 1.0f);
	//	glzDirectSpriteRenderAtlasPixelPerfect(192, 192, 1, 64, 64, 4, 4, 1, glzOrigin::BOTTOM_LEFT);
	//	glzDirectSpriteRenderAtlasPixelPerfectQuantized(208, 192, 1, 64, 64, 4, 4, 1, 16.0f, glzOrigin::BOTTOM_LEFT);




	}




	glUseProgram(0);
	glFlush ();													// Flush The GL Rendering Pipeline
}
