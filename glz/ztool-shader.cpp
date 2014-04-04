// Copyright 2013 Peter Wallstr�m
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

// glz shader toolkit - Warning does not produce actual shade
// visit http://www.flashbang.se or contact me at overlord@flashbang.se
// the entire toolkit should exist in it's entirety at github
// https://github.com/zeoverlord/glz.git

#include <fstream>
#include <string.h>
#include "ztool-shader.h"
#include <stdio.h>
#include <windows.h>													// Header File For The Windows Library
#include <gl/gl.h>														// Header File For The OpenGL32 Library
#include <gl/glu.h>														// Header File For The GLu32 Library
#include <gl/glext.h>
using namespace std;


static PFNGLBINDATTRIBLOCATIONPROC				glBindAttribLocation;

static PFNGLDELETESHADERPROC					glDeleteShader;
static PFNGLGETSHADERIVPROC						glGetShaderiv;
static PFNGLGETPROGRAMIVPROC					glGetProgramiv;
static PFNGLPROGRAMPARAMETERIARBPROC			glProgramParameteri;

static PFNGLDETACHSHADERPROC                    glDetachShader;
static PFNGLCREATESHADERPROC			        glCreateShader;
static PFNGLSHADERSOURCEPROC                    glShaderSource;
static PFNGLCOMPILESHADERPROC                   glCompileShader;
static PFNGLCREATEPROGRAMPROC					glCreateProgram;
static PFNGLATTACHSHADERPROC					glAttachShader;
static PFNGLLINKPROGRAMPROC                     glLinkProgram;
static PFNGLUSEPROGRAMPROC						glUseProgram;
static PFNGLVALIDATEPROGRAMPROC                 glValidateProgram;


static PFNGLUNIFORM1FARBPROC                       glUniform1fARB;
static PFNGLUNIFORM2FARBPROC                       glUniform2fARB;
static PFNGLUNIFORM3FARBPROC                       glUniform3fARB;
static PFNGLUNIFORM4FARBPROC                       glUniform4fARB;
static PFNGLUNIFORM1IARBPROC                       glUniform1iARB;
static PFNGLUNIFORM2IARBPROC                       glUniform2iARB;
static PFNGLUNIFORM3IARBPROC                       glUniform3iARB;
static PFNGLUNIFORM4IARBPROC                       glUniform4iARB;
static PFNGLUNIFORM1FVARBPROC                      glUniform1fvARB;
static PFNGLUNIFORM2FVARBPROC                      glUniform2fvARB;
static PFNGLUNIFORM3FVARBPROC                      glUniform3fvARB;
static PFNGLUNIFORM4FVARBPROC                      glUniform4fvARB;
static PFNGLUNIFORM1IVARBPROC                      glUniform1ivARB;
static PFNGLUNIFORM2IVARBPROC                      glUniform2ivARB;
static PFNGLUNIFORM3IVARBPROC                      glUniform3ivARB;
static PFNGLUNIFORM4IVARBPROC                      glUniform4ivARB;
static PFNGLUNIFORMMATRIX2FVPROC                glUniformMatrix2fv;
static PFNGLUNIFORMMATRIX3FVPROC                glUniformMatrix3fv;
static PFNGLUNIFORMMATRIX4FVPROC                glUniformMatrix4fv;

static PFNGLGETUNIFORMFVPROC				    glGetUniformfv;
static PFNGLGETUNIFORMIVPROC					glGetUniformiv;
static PFNGLGETSHADERINFOLOGPROC                glGetShaderInfoLog;
static PFNGLGETATTACHEDSHADERSPROC              glGetAttachedShaders;
static PFNGLGETUNIFORMLOCATIONPROC              glGetUniformLocation;
static PFNGLGETACTIVEUNIFORMPROC                glGetActiveUniform;
static PFNGLGETSHADERSOURCEPROC                 glGetShaderSource;

static bool isinited_shd;

static unsigned int passtroughprogram;



char vertexpasstrough[] =

"#version 140\r\n"
""
"in vec3 Position;"
"in vec2 TexCoord;"
"out vec4 tc;"
"void main() {"
"	gl_Position = vec4(Position.xyz, 1.0);"
"	tc = vec4(TexCoord.xy, 0.0, 1.0);"
"}"
"";

char fragmentpasstrough[] =
"#version 140\r\n"
""
"in vec4 tc;"
"out vec4 fragment_color;"
"uniform sampler2D texunit0;"
"void main() {"
	"vec4 base = texture2D(texunit0, tc.xy);"
	"fragment_color = base;"
"}"
"";


// now i made all of these static, so you shouldn't have to initialize them again
void ini_shd(void)
{
	isinited_shd=true;
	glBindAttribLocation= (PFNGLBINDATTRIBLOCATIONPROC) wglGetProcAddress("glBindAttribLocation");
	
	glDeleteShader				= (PFNGLDELETESHADERPROC) wglGetProcAddress("glDeleteShader");
	glDetachShader				= (PFNGLDETACHSHADERPROC) wglGetProcAddress("glDetachShader");
	glCreateShader				= (PFNGLCREATESHADERPROC) wglGetProcAddress("glCreateShader");
	glShaderSource				= (PFNGLSHADERSOURCEPROC) wglGetProcAddress("glShaderSource");
	glCompileShader				= (PFNGLCOMPILESHADERPROC) wglGetProcAddress("glCompileShader");
	glCreateProgram				= (PFNGLCREATEPROGRAMPROC) wglGetProcAddress("glCreateProgram");
	glAttachShader				= (PFNGLATTACHSHADERPROC) wglGetProcAddress("glAttachShader");
	glLinkProgram				= (PFNGLLINKPROGRAMPROC) wglGetProcAddress("glLinkProgram");
	glUseProgram				= (PFNGLUSEPROGRAMPROC) wglGetProcAddress("glUseProgram");
	glValidateProgram			= (PFNGLVALIDATEPROGRAMPROC) wglGetProcAddress("glValidateProgram");
	glGetShaderiv				= (PFNGLGETSHADERIVPROC) wglGetProcAddress("glGetShaderiv");
	glGetProgramiv				= (PFNGLGETPROGRAMIVPROC) wglGetProcAddress("glGetProgramiv");
	glProgramParameteri				= (PFNGLPROGRAMPARAMETERIARBPROC) wglGetProcAddress("glProgramParameteri");
	
	glGetShaderInfoLog			= (PFNGLGETSHADERINFOLOGPROC) wglGetProcAddress("glGetShaderInfoLog");
	glGetAttachedShaders		= (PFNGLGETATTACHEDSHADERSPROC) wglGetProcAddress("glGetAttachedShaders");
	glGetUniformLocation		= (PFNGLGETUNIFORMLOCATIONPROC) wglGetProcAddress("glGetUniformLocation");
	glGetActiveUniform			= (PFNGLGETACTIVEUNIFORMPROC) wglGetProcAddress("glGetActiveUniform");
	glGetUniformfv				= (PFNGLGETUNIFORMFVPROC) wglGetProcAddress("glGetUniformfv");
	glGetUniformiv				= (PFNGLGETUNIFORMIVPROC) wglGetProcAddress("glGetUniformiv");
	glGetShaderSource			= (PFNGLGETSHADERSOURCEPROC) wglGetProcAddress("glGetShaderSource");
                                                                     
	glUniform1fARB= (PFNGLUNIFORM1FARBPROC) wglGetProcAddress("glUniform1fARB");
	glUniform2fARB= (PFNGLUNIFORM2FARBPROC) wglGetProcAddress("glUniform2fARB");
	glUniform3fARB= (PFNGLUNIFORM3FARBPROC) wglGetProcAddress("glUniform3fARB");
	glUniform4fARB= (PFNGLUNIFORM4FARBPROC) wglGetProcAddress("glUniform4fARB");
	glUniform1iARB= (PFNGLUNIFORM1IARBPROC) wglGetProcAddress("glUniform1iARB");
	glUniform2iARB= (PFNGLUNIFORM2IARBPROC) wglGetProcAddress("glUniform2iARB");
	glUniform3iARB= (PFNGLUNIFORM3IARBPROC) wglGetProcAddress("glUniform3iARB");
	glUniform4iARB= (PFNGLUNIFORM4IARBPROC) wglGetProcAddress("glUniform4iARB");
	glUniform1fvARB= (PFNGLUNIFORM1FVARBPROC) wglGetProcAddress("glUniform1fvARB");
	glUniform2fvARB= (PFNGLUNIFORM2FVARBPROC) wglGetProcAddress("glUniform2fvARB");
	glUniform3fvARB= (PFNGLUNIFORM3FVARBPROC) wglGetProcAddress("glUniform3fvARB");
	glUniform4fvARB= (PFNGLUNIFORM4FVARBPROC) wglGetProcAddress("glUniform4fvARB");
	glUniform1ivARB= (PFNGLUNIFORM1IVARBPROC) wglGetProcAddress("glUniform1ivARB");
	glUniform2ivARB= (PFNGLUNIFORM2IVARBPROC) wglGetProcAddress("glUniform2ivARB");
	glUniform3ivARB= (PFNGLUNIFORM3IVARBPROC) wglGetProcAddress("glUniform3ivARB");
	glUniform4ivARB= (PFNGLUNIFORM4IVARBPROC) wglGetProcAddress("glUniform4ivARB");
	glUniformMatrix2fv= (PFNGLUNIFORMMATRIX2FVPROC) wglGetProcAddress("glUniformMatrix2fv");
	glUniformMatrix3fv= (PFNGLUNIFORMMATRIX3FVPROC) wglGetProcAddress("glUniformMatrix3fv");
	glUniformMatrix4fv= (PFNGLUNIFORMMATRIX4FVPROC) wglGetProcAddress("glUniformMatrix4fv");


	passtroughprogram = glzShaderLoadString(vertexpasstrough, fragmentpasstrough, glzVAOType::AUTO);
	glzShaderLink(passtroughprogram);

	
}



unsigned long getFileLength(ifstream& file)
{
    if(!file.good()) return 0;
    
//    unsigned long pos=file.tellg();
    file.seekg(0,ios::end);
    unsigned long len = file.tellg();
    file.seekg(ios::beg);
    
    return len;
}


// these next 3 functions will load a file, compile it and attach it to a program object
void loadVShadeString(unsigned int program, char *shadercode)  //loads a vertex shader in glsl format
{

	unsigned int  VertexShaderObject;

	// start compilling the source
	VertexShaderObject = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShaderObject, 1, (const char **)&shadercode, NULL);

	int compiled = 0;
	char str[4096];
	// Compile the vertex and fragment shader, and print out any arrors

	glCompileShader(VertexShaderObject);
	glGetShaderiv(VertexShaderObject, GL_COMPILE_STATUS, &compiled);

	if (!compiled) {

		glGetShaderInfoLog(VertexShaderObject, sizeof(str), NULL, str);
		MessageBoxA(NULL, str, "vertex Shader Compile Error", MB_OK | MB_ICONEXCLAMATION);
		return;
	}

	glAttachShader(program, VertexShaderObject);

	glDeleteShader(VertexShaderObject);

	return;
}



void loadFShadeString(unsigned int program, char *shadercode)  //dito on a fragment shader
{

	unsigned int  FragmentShaderObject;

	// start compilling the source
	FragmentShaderObject = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShaderObject, 1, (const char **)&shadercode, NULL);

	int compiled = 0;
	char str[4096];
	// Compile the vertex and fragment shader, and print out any arrors

	glCompileShader(FragmentShaderObject);
	glGetShaderiv(FragmentShaderObject, GL_COMPILE_STATUS, &compiled);

	if (!compiled) {

		glGetShaderInfoLog(FragmentShaderObject, sizeof(str), NULL, str);
		MessageBoxA(NULL, str, "vertex Shader Compile Error", MB_OK | MB_ICONEXCLAMATION);
		return;
	}

	glAttachShader(program, FragmentShaderObject);


	glDeleteShader(FragmentShaderObject);

	return;
}




// these next 3 functions will load a file, compile it and attach it to a program object
void loadVShade(unsigned int program, char filename[160])  //loads a vertex shader in glsl format
{

	unsigned int  VertexShaderObject;
	char*     VertexShaderSource;
	ifstream file;
    file.open(filename, ios::in);
	if(!file) {return;}
    
    unsigned long len = getFileLength(file);
    
    if (len==0) { return;}   // "Empty File" 
    
    
    VertexShaderSource = new char[len+1];
    if (VertexShaderSource == 0) {return;}   // can't reserve memory
    
    VertexShaderSource[len] = 0;  // len isn't always strlen cause some characters are stripped in ascii read...
                            // it is important to 0-terminate the real length later, len is just max possible value...
   
    unsigned int i=0;
    while (file.good())
    {
        VertexShaderSource[i++] = file.get();       // get character from file
        if (i>len) i=len;   // coding guidelines...
    }
    i--;
    VertexShaderSource[i] = 0;  // 0 terminate it.
    
    file.close();   

	// i just have to say this about file loading, it is bloddy anoying, this should be like a single line
	// and maybe it will whenever i get arround to doing the packed file loading i want to do.


	// start compilling the source
	VertexShaderObject = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShaderObject, 1, (const char **)&VertexShaderSource, NULL);

	delete[] VertexShaderSource;

	int compiled = 0;
	char str[4096];
	// Compile the vertex and fragment shader, and print out any arrors

	glCompileShader(VertexShaderObject);
	glGetShaderiv(VertexShaderObject,GL_COMPILE_STATUS, &compiled);

	if (!compiled) {

		glGetShaderInfoLog( VertexShaderObject, sizeof(str), NULL, str );
		MessageBoxA( NULL, str, "vertex Shader Compile Error", MB_OK|MB_ICONEXCLAMATION );
	    return;
	}

	glAttachShader(program,VertexShaderObject);

	glDeleteShader(VertexShaderObject);

	return;
}





void loadFShade(unsigned int program, char filename[160])  //dito on a fragment shader
{

	unsigned int  FragmentShaderObject;
	char*     FragmentShaderSource;


	ifstream file;
    file.open(filename, ios::in);
    if(!file) {return;}
    
    unsigned long len = getFileLength(file);
    
    if (len==0) { return;}   // "Empty File" 
    
    
    FragmentShaderSource =  new char[len+1];
    if (FragmentShaderSource == 0) { return;}   // can't reserve memory
    
    FragmentShaderSource[len] = 0;  // len isn't always strlen cause some characters are stripped in ascii read...
                            // it is important to 0-terminate the real length later, len is just max possible value...
   
    unsigned int i=0;
    while (file.good())
    {
        FragmentShaderSource[i++] = file.get();       // get character from file
        if (i>len) i=len;   // coding guidelines...
    }
    
	i--;
    FragmentShaderSource[i] = 0;  // 0 terminate it.
    
    file.close();   

	// start compilling the source
	FragmentShaderObject = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShaderObject, 1, (const char **)&FragmentShaderSource, NULL);

	delete[] FragmentShaderSource;

	int compiled = 0;
	char str[4096];
	// Compile the vertex and fragment shader, and print out any arrors

	glCompileShader(FragmentShaderObject);
	glGetShaderiv(FragmentShaderObject,GL_COMPILE_STATUS, &compiled);

	if (!compiled) {

		glGetShaderInfoLog( FragmentShaderObject, sizeof(str), NULL, str );
		MessageBoxA( NULL, str, "vertex Shader Compile Error", MB_OK|MB_ICONEXCLAMATION );
	    return;
	}

	glAttachShader(program,FragmentShaderObject);

	
	glDeleteShader(FragmentShaderObject);

	return;
}



void loadGShade(unsigned int program, char filename[160])  //dito on a fragment shader
{

	
	unsigned int  GeometryShaderObject;
	char*     GeometryShaderSource;

	ifstream file;
    file.open(filename, ios::in);
    if(!file) {return;}
    
    unsigned long len = getFileLength(file);
    
    if (len==0) {return;}   // "Empty File" 
    
    
    GeometryShaderSource =  new char[len+1];
    if ( GeometryShaderSource == 0) {return;}   // can't reserve memory
    
     GeometryShaderSource[len] = 0;  // len isn't always strlen cause some characters are stripped in ascii read...
                            // it is important to 0-terminate the real length later, len is just max possible value...
   
    unsigned int i=0;
    while (file.good())
    {
         GeometryShaderSource[i++] = file.get();       // get character from file
        if (i>len) i=len;   // coding guidelines...
    }
    
	i--;
     GeometryShaderSource[i] = 0;  // 0 terminate it.
   
    file.close();  

	// start compilling the source
	GeometryShaderObject = glCreateShader(GL_GEOMETRY_SHADER);
	glShaderSource(GeometryShaderObject, 1, (const char **)&GeometryShaderSource, NULL);

	delete[] GeometryShaderSource;

	int compiled = 0;
	char str[4096];
	// Compile the vertex and fragment shader, and print out any arrors

	glCompileShader(GeometryShaderObject);
	glGetShaderiv(GeometryShaderObject,GL_COMPILE_STATUS, &compiled);

	if (!compiled) {

		glGetShaderInfoLog( GeometryShaderObject, sizeof(str), NULL, str );
		MessageBoxA( NULL, str, "vertex Shader Compile Error", MB_OK|MB_ICONEXCLAMATION );
	    return;
	}

	glAttachShader(program,GeometryShaderObject);
	
	glDeleteShader(GeometryShaderObject);

	return;
}

// this specific function will only work if you have openGL 3.2 installed because of the geometry shader which should be any dx 10 class hardware, basically gf8xxx and above

unsigned int glzShaderLoadString(char *vert, char *frag, glzVAOType type)
{
	if (!isinited_shd) ini_shd();

	unsigned int  program;

	program = glCreateProgram();


	loadVShadeString(program, vert);
	loadFShadeString(program, frag);


	if (type == glzVAOType::AUTO)
	{
		glBindAttribLocation(program, 0, "Position");
		glBindAttribLocation(program, 1, "TexCoord");
		glBindAttribLocation(program, 2, "Normal");
	}

	return program;
}

unsigned int glzShaderLoad(char file_vert[255], char file_geo[255], char file_frag[255], glzVAOType type)
{
	if(!isinited_shd) ini_shd();

	unsigned int  program;

	program	   = glCreateProgram();
		

	loadVShade(program, file_vert);
	loadGShade(program, file_geo);
	loadFShade(program, file_frag);

	
	if (type == glzVAOType::AUTO)
	{	
	glBindAttribLocation(program,0, "Position");
	glBindAttribLocation(program,1, "TexCoord");
	glBindAttribLocation(program,2, "Normal");
	}

    return program;
}

// this function loads only the certex and fragment programs and like the above it sets the vertex attribute locations
// in the rare case you want to set these yourself then use any number you like above lets say 5, its really 1 but i might add support for like just vertex + texture and such later on
// one thing to note is that the program is not linked, that function is lower down
unsigned int glzShaderLoad(char file_vert[255], char file_frag[255], glzVAOType type)
{
	if(!isinited_shd) ini_shd();

	unsigned int  program;

	program	   = glCreateProgram();
		

	loadVShade(program, file_vert);
	loadFShade(program, file_frag);
	
	if (type == glzVAOType::AUTO)
	{	
	glBindAttribLocation(program,0, "Position");
	glBindAttribLocation(program,1, "TexCoord");
	glBindAttribLocation(program,2, "Normal");
	}

    return program;

}


// this program links the program, this is so that you can set up some custom settings, like those for the geometry shader, i will refer you to my geometry shader tutorials for that
void glzShaderLink(unsigned int program)
{
	if(!isinited_shd) ini_shd();

	int linked   = 0;

	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS,&linked);

	if (!linked) {
		MessageBoxA (HWND_DESKTOP, "can't link shaders", "Error", MB_OK | MB_ICONEXCLAMATION);
	    return;
	}


return;
}



void glzShaderUsePasstrough(void)
{
	if (!isinited_shd) ini_shd();

	unsigned int loc2 = glGetUniformLocation(passtroughprogram, "texunit0");
	glUniform1iARB(loc2, 0);
	glUseProgram(passtroughprogram);
	return;
}


// now this is all pretty basic stuff but here is a list of things i like to add later on

// shader script, which is basically a single file you call with all the shaders in it and how to load it.
// tesselation shader support
// precompiled shaders
// in code loading, which is more or less using an array to load a shader
// default shaders, much like those included in the toolkit but allready defined in the code using the above function to load them.