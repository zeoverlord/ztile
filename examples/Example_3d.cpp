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
// git:// [future home of github link]



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
#include "..\glz\ztool-tex.h"

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
float m[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
unsigned int texture[5],fonttexture[15];


char tbuffer[160];
char tbuffer2[160];
float texttimer=0;
float spriteframetimer=0;
int spriteframe=0;

float q[4] ={1,0,0,0};
float q2[4] ={1,0,0,0};
float q3[4] ={1,0,0,0};

int gamestate=1;

img_head img;
unsigned char *data;


GLhandleARB  ProgramObject,ProgramObjectFT,ProgramObjectFSQ;
texture_transform text_tt;

static PFNGLUSEPROGRAMPROC						glUseProgram;
static PFNGLUNIFORM1IPROC                       glUniform1i;
static PFNGLUNIFORMMATRIX4FVPROC                glUniformMatrix4fv;
static PFNGLUNIFORM4FARBPROC                    glUniform4f;
static PFNGLGETUNIFORMLOCATIONPROC              glGetUniformLocation;


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

	glClearColor (0.0f, 0.0f, 0.0f, 0.5f);						// Black Background
	glClearDepth (1.0f);										// Depth Buffer Setup
	glDepthFunc (GL_LEQUAL);									// The Type Of Depth Testing (Less Or Equal)
	glEnable (GL_DEPTH_TEST);									// Enable Depth Testing
	glShadeModel (GL_SMOOTH);									// Select Smooth Shading
	glHint (GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);			// Set Perspective Calculations To Most Accurate



	glUseProgram				= (PFNGLUSEPROGRAMPROC) wglGetProcAddress("glUseProgram");
	glGetUniformLocation		= (PFNGLGETUNIFORMLOCATIONPROC) wglGetProcAddress("glGetUniformLocation");                                                                     
	glUniform1i= (PFNGLUNIFORM1IPROC) wglGetProcAddress("glUniform1i");
	glUniform4f= (PFNGLUNIFORM4FARBPROC) wglGetProcAddress("glUniform4fARB");
	glUniformMatrix4fv= (PFNGLUNIFORMMATRIX4FVPROC) wglGetProcAddress("glUniformMatrix4fv");




	float mt[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	float mt2[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	float mt3[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	float mo[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	float mg[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	float mh[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

	unsigned int ad[64]={2,2,2,1,2,2,2,2,
						 2,2,4,1,4,2,2,2,
						 3,3,0,1,0,3,3,3,
						 3,3,0,1,0,3,3,3,
						 2,2,4,1,4,2,2,2,
						 2,2,2,1,2,2,2,2,
						 2,2,2,1,1,1,1,1,
						 2,2,2,2,2,2,2,2};





	glzLoadIdentity(mt);
	glzLoadIdentity(mt2);
	glzLoadIdentity(mt3);
	glzLoadIdentity(mo);
	glzLoadIdentity(mg);
	glzLoadIdentity(mh);

	
	
	//glzTranslatef(mt,-3.9f,1.9f,0);
	glzTranslatef(mg,0,0,0);	

	glzScalef(mt,0.17f,0.17f,0.17f);
	glzScalef(mt2,0.3f,0.3f,0.3f);
	glzScalef(mt3,0.13f,0.13f,0.13f);
	glzScalef(mg,32.0f,32.0f,32.0f);
	glzScalef(mh,0.4f,0.4f,0.4f);

	glzRotatef(mh,90,1.0f,0.0f,0.0f);

	glzTranslatef(mh,-8.0,8.0,0.0);

	text_tt=glzMakeTTAtlas(16,16,0);

// primitive screen
	textvao_num[0]=glzVAOMakeText("Primitives", mt, 0.7f, text_tt, &textvao[0]);
 
// wavefront objects screen

	textvao_num[1]=glzVAOMakeText(".obj loading, try using the arrow keys", mt, 0.7f, text_tt, &textvao[1]);
	
// heigth grid screen

	textvao_num[2]=glzVAOMakeText("Heightfield", mt, 0.7f, text_tt, &textvao[2]);


// all screens
	textvao_num[15]=glzVAOMakeText("Switch screens with 1, 2, 3", mt3, 0.7f, text_tt, &textvao[15]);


	
	primitive_gen primitives[10];	

	primitives[0]=glzMakePGDefault(GLZ_PRIMITIVE_CUBE);
	primitives[0].tt=glzMakeTTDefault();

	primitives[1]=glzMakePGDefault(GLZ_PRIMITIVE_PYRAMID);
	primitives[1].tt=glzMakeTTDefault();

	primitives[2]=glzMakePGDefault(GLZ_PRIMITIVE_TETRAHEDRON);
	primitives[2].tt=glzMakeTTDefault();
		
	primitives[3]=glzMakePGDefault(GLZ_PRIMITIVE_OCTAHEDRON);
	primitives[3].tt=glzMakeTTDefault();
		
	primitives[4]=glzMakePGDefault(GLZ_PRIMITIVE_DODECAHEDRON);
	primitives[4].tt=glzMakeTTDefault();
		
	primitives[5]=glzMakePGDefault(GLZ_PRIMITIVE_ICOSAHEDRON);
	primitives[5].tt=glzMakeTTDefault();

	primitives[6]=glzMakePGDefault(GLZ_PRIMITIVE_ICOSIDODECAHEDRON);
	primitives[6].tt=glzMakeTTDefault();




	vao_num[1]=glzVAOMakePrimitive(primitives[0], &vao[1]); // change the first argument to 2 for an extra object, this is subject to some major redecorating
	vao_num[2]=glzVAOMakePrimitive(primitives[1], &vao[2]); // change the first argument to 2 for an extra object, this is subject to some major redecorating
	vao_num[3]=glzVAOMakePrimitive(primitives[2], &vao[3]); // change the first argument to 2 for an extra object, this is subject to some major redecorating
	vao_num[4]=glzVAOMakePrimitive(primitives[3], &vao[4]); // change the first argument to 2 for an extra object, this is subject to some major redecorating
	vao_num[5]=glzVAOMakePrimitive(primitives[4], &vao[5]); // change the first argument to 2 for an extra object, this is subject to some major redecorating
	vao_num[6]=glzVAOMakePrimitive(primitives[5], &vao[6]); // change the first argument to 2 for an extra object, this is subject to some major redecorating
	vao_num[7]=glzVAOMakePrimitive(primitives[6], &vao[7]); // change the first argument to 2 for an extra object, this is subject to some major redecorating


	texture_transform obj_tt=glzMakeTTDefault();
	vao_num[8]=glzVAOMakeFromFile("data\\objects\\cv9040c.obj",mo, obj_tt, &vao[8]);

	glzReadTgaHead(&img, "data\\heightmap.tga");
	data = new unsigned char[img.imageSize];
	glzLoadTga(&img,"data\\heightmap.tga", data);

	
	texture_transform height_tt=glzMakeTTVertexCoordAdopt(1.0f,1.0f,GLZ_AXIS_Z);
	image_geo_transform igt=glzMakeIGT(GLZ_IGT_DISPLACE_ADD,img.m_width,img.m_height,img.m_bpp,0,0,0,2.0f,32.0,GLZ_AXIS_Z, data);
	vao_num[9]=glzVAOMakeHeightAtlasGrid(16, 16, mh, height_tt, igt, &vao[9]);
	
	delete[] data;
	data=NULL;




	ProgramObject=glzShaderLoad("data\\glsl.vert","data\\glsl.frag",GLZ_AUTO);
	glzShaderLink(ProgramObject);

	// load the textures
	fonttexture[0]=glzLoadTexture("data\\fonts\\arial.tga",GLZ_FILTER_LINEAR);

	texture[0]=glzLoadTexture("data\\back.tga",GLZ_FILTER_ANSIO_MAX);
	texture[2]=glzLoadTexture("data\\cv90base.tga",GLZ_FILTER_ANSIO_MAX);
	texture[4]=glzLoadTexture("data\\gridlines.tga",GLZ_FILTER_ANSIO_MAX);




	return TRUE;												// Return TRUE (Initialization Successful)
}


void Deinitialize (void)										// Any User DeInitialization Goes Here
{

	// this shouldn't normally be nessecary, but it's better to make it a habit to delete data for when you start to load and unload resources mid game.

	glzKillAllVAO();		// deletes all vaos in existance


}

void Update (float seconds)								// Perform Motion Updates Here
{

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

		glzRotateQuaternionf(q,seconds*50,0.0f,1.0f,0.0f);	
		glzRotateQuaternionf(q,seconds*40,1.0f,0.0f,0.0f);	


	}

	if (gamestate==2)
	{
	if (g_keys->keyDown [VK_UP] == TRUE)glzRotateQuaternionf(q2,seconds*40,1.0f,0.0f,0.0f);	
	if (g_keys->keyDown [VK_DOWN] == TRUE)glzRotateQuaternionf(q2,seconds*-40,1.0f,0.0f,0.0f);	

	if (g_keys->keyDown [VK_LEFT] == TRUE)glzRotateQuaternionf(q2,seconds*40,0.0f,1.0f,0.0f);	
	if (g_keys->keyDown [VK_RIGHT] == TRUE)glzRotateQuaternionf(q2,seconds*-40,0.0f,1.0f,0.0f);	
	}


if (gamestate==3)
	{	

		glzRotateQuaternionf(q3,seconds*50,0.0f,1.0f,0.0f);	
	}


	if (g_keys->keyDown ['1'] == TRUE) gamestate=1;
	if (g_keys->keyDown ['2'] == TRUE) gamestate=2;
	if (g_keys->keyDown ['3'] == TRUE) gamestate=3;

}



void draw_text(float x, float y, int text, int font, unsigned int po, unsigned int col)
{
	glUseProgram(po);

	unsigned int loc1 = glGetUniformLocation(po,"projMat");
	unsigned int loc2 = glGetUniformLocation(po,"texunit0");
	unsigned int loc3 = glGetUniformLocation(po,"tint");
	glzLoadIdentity(m);
	glzOrtho(m, -4, 4, -2, 2, -100, 100);
	glzTranslatef(m,x,y,0);

	glUniformMatrix4fv(loc1, 1, GL_FALSE, m);

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


void draw_object(unsigned int tx,int prim, float x, float y)
{
	unsigned int loc1 = glGetUniformLocation(ProgramObject,"projMat");
	// draw objects
	glzLoadIdentity(m);
	glzPerspective(m, 45.0f, 1.618f, 1.0f, 1000.0f);

	glzTranslatef(m,x,y,-7);	
	//glzScalef(m,0.1,0.1,0.1);
	glzQuaternionToMatrixf(m,q);
	glUniformMatrix4fv(loc1, 1, GL_FALSE, m);	

    glBindTexture(GL_TEXTURE_2D,texture[tx]);
	glzDrawVAO(vao_num[prim],vao[prim],GL_TRIANGLES);
}


void Draw (void)
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear Screen And Depth Buffer
	
	glEnable(GL_TEXTURE_2D);
	unsigned int loc1 = glGetUniformLocation(ProgramObject,"projMat");
	unsigned int loc2 = glGetUniformLocation(ProgramObject,"texunit0");
	unsigned int loc3 = glGetUniformLocation(ProgramObject,"tint");

	unsigned int loc4 = glGetUniformLocation(ProgramObjectFT,"projMat");
	unsigned int loc5 = glGetUniformLocation(ProgramObjectFT,"texunit0");

	glUseProgram(ProgramObject);
	glUniform1i(loc2, 0);	
	glUniform4f(loc3, 1.0f,1.0f,1.0f,1.0f);

	// i have used these gamestates in a few games for LD48 now and they are really quick and dirty, but effective.
	// they allow you to quickly make a title screen and end screen at the end of the project without changing that much code, instead you just encapsulate it in a gamestate

	if (gamestate==1)  
	{

		draw_object(0,1,-2.5f,1.5f);  // the cube only looks larger, but that's just because all primitives are made to fit within 0.5 to -0.5 cube, and naturally the cube fills that space perfectly
		draw_object(0,2,0.0f,1.5f);
		draw_object(0,3,2.5f,1.5f);

		draw_object(0,4,-2.7f,-1.5f);
		draw_object(0,5,-1.0f,-1.5f);
		draw_object(0,6,1.0f,-1.5f);
		draw_object(0,7,2.5f,-1.5f);



		draw_text(-3.9f, 1.9f,0,0,ProgramObject,COL_WHITE);
		draw_text(1.7f, -1.8f,15,0,ProgramObject,COL_WHITE);
	}




	if (gamestate==2)
	{

		// draw tank
	glzLoadIdentity(m);
	glzPerspective(m, 45.0f, 1.618f, 1.0f, 100.0f);
	glzTranslatef(m,0,-2,-17);	
	glzScalef(m,0.5,0.5,0.5);
	glzQuaternionToMatrixf(m,q2);
	glUniformMatrix4fv(loc1, 1, GL_FALSE, m);	

    glBindTexture(GL_TEXTURE_2D,texture[2]);
	glzDrawVAO(vao_num[8],vao[8],GL_TRIANGLES);
			
		draw_text(-3.9f, 1.9f,1,0,ProgramObject,COL_WHITE);
		draw_text(1.7f, -1.8f,15,0,ProgramObject,COL_WHITE);
	
	}	


	if (gamestate==3)
	{	

			// draw height grid
		glzLoadIdentity(m);
		glzPerspective(m, 45.0f, 1.618f, 1.0f, 100.0f);
		glzTranslatef(m,0,-1,-7);	
		glzQuaternionToMatrixf(m,q3);
		glUniformMatrix4fv(loc1, 1, GL_FALSE, m);	

		glBindTexture(GL_TEXTURE_2D,texture[4]);
		glzDrawVAO(vao_num[9],vao[9],GL_TRIANGLES);
		
		draw_text(-3.9f, 1.9f,2,0,ProgramObject,COL_WHITE);
		draw_text(1.7f, -1.8f,15,0,ProgramObject,COL_WHITE);
	}

	


	glUseProgram(0);
	glFlush ();													// Flush The GL Rendering Pipeline
}
