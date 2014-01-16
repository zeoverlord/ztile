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

// glz geometry toolkit - for allmost all your geometry needs
// visit http://www.flashbang.se or contact me at overlord@flashbang.se
// the entire toolkit should exist in it's entirety at github
// https://github.com/zeoverlord/glz.git


#include <fstream>
#include <math.h>
#include <string.h>
#include "ztool-geo.h"
#include "ztool-glz.h"
#include <stdio.h>
#include <windows.h>													// Header File For The Windows Library
#include <gl/gl.h>														// Header File For The OpenGL32 Library
#include <gl/glu.h>														// Header File For The GLu32 Library
#include <gl/glext.h>

#include <vector>

using namespace std;

static PFNGLGENBUFFERSPROC					glGenBuffers;					// VBO Name Generation Procedure
static PFNGLBINDBUFFERPROC					glBindBuffer;					// VBO Bind Procedure
static PFNGLBUFFERDATAPROC					glBufferData;					// VBO Data Loading Procedure
static PFNGLDELETEBUFFERSPROC				glDeleteBuffers;				// VBO Deletion Procedure

// VAO

static PFNGLBINDVERTEXARRAYPROC					glBindVertexArray;
static PFNGLDELETEVERTEXARRAYSPROC				glDeleteVertexArrays;
static PFNGLGENVERTEXARRAYSPROC					glGenVertexArrays;
static PFNGLISVERTEXARRAYPROC					glIsVertexArray;

static PFNGLVERTEXATTRIBPOINTERPROC				glVertexAttribPointer;
static PFNGLBINDATTRIBLOCATIONPROC				glBindAttribLocation;
static PFNGLDISABLEVERTEXATTRIBARRAYPROC		glDisableVertexAttribArray;
static PFNGLENABLEVERTEXATTRIBARRAYPROC			glEnableVertexAttribArray;

static PFNGLGETVERTEXATTRIBIUIVPROC			glGetVertexAttribIuiv;
static PFNGLISBUFFERARBPROC			glIsBuffer;


static bool isinited_geo;
static int active_vao[1024];

// most of the functions below are booring stuff and will not be commented on as they are pretty mic self explanatory
// it's mostly just setting up primitives, generating geometry and setting up structures
// but if you like to make your own primitive there are two easy ways, either copy the arrays in primitives.h or set something up like the below function glzPrimCubeverts



long glzPrimCubeverts(float *v, float *t, float *n)
{
	float vt[] =
	{
		-0.5f, 0.5f, -0.5f, //top
		-0.5f, 0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
		0.5f, 0.5f, -0.5f,
		-0.5f, 0.5f, -0.5f,
		0.5f, 0.5f, 0.5f,

		-0.5f, -0.5f, -0.5f, // bottom
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, 0.5f,
		-0.5f, -0.5f, 0.5f,
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, 0.5f,

		-0.5f, -0.5f, 0.5f, // front
		0.5f, -0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
		-0.5f, 0.5f, 0.5f,
		-0.5f, -0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,

		0.5f, -0.5f, -0.5f, // right
		0.5f, 0.5f, -0.5f,
		0.5f, 0.5f, 0.5f,
		0.5f, -0.5f, 0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, 0.5f, 0.5f,

		-0.5f, -0.5f, -0.5f, // back
		-0.5f, 0.5f, -0.5f,
		0.5f, 0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		0.5f, 0.5f, -0.5f,

		-0.5f, -0.5f, -0.5f, // left
		-0.5f, -0.5f, 0.5f,
		-0.5f, 0.5f, 0.5f,
		-0.5f, 0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, 0.5f, 0.5f
	};


	float tt[] =
	{
		0.0f, 1.0f, //top
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		1.0f, 0.0f,

		1.0f, 1.0f, // bottom
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 0.0f,

		0.0f, 0.0f, // front
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 1.0f,

		1.0f, 0.0f, // right
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 1.0f,

		1.0f, 0.0f, // back
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 1.0f,

		0.0f, 0.0f, // left
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 1.0f
	};

	float nt[] =
	{
		0.0f, 1.0f, 0.0f, //top
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,

		0.0f, -1.0f, 0.0f, // bottom
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,

		0.0f, 0.0f, 1.0f, // front
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,

		1.0f, 0.0f, 0.0f, // right
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,

		0.0f, 0.0f, -1.0f, // back
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,

		-1.0f, 0.0f, 0.0f, // left
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f
	};

	memcpy(v, vt, 36 * 3 * 4);
	memcpy(t, tt, 36 * 2 * 4);
	memcpy(n, nt, 36 * 3 * 4);

	return 36;
}


long glzCountFromIndexArrays(long vert_face[],int enteries)
{

	int faces=enteries;

	int i=2,origin=0,c=0;

 	while(i<faces)
	{
		
		if(vert_face[i]==-1)
		{
			origin=i+1;
			i=origin+2;
				
		}
		if (origin<faces)
		{
			c+=3;

		}

		i++;		

	}

	return c;


}




// public stuff

void addToVaoList(unsigned int vao)
{
	int i=0;

	while (active_vao[i]!=-1)
	{
		i++;
		if (i==1023) return;
	}

	active_vao[i]=vao;
	return;
}

void removeFromVaoList(unsigned int vao)
{
	int i=0;

	while (active_vao[i]!=vao)
	{
		i++;
		if (i==1023) return;
	}

	active_vao[i]=-1;
	return;
}


void ini_geo(void)
{

	int i = 0;

	while (i<1024)
	{
		active_vao[i] = -1;
		i++;
	}

	glGenBuffers = (PFNGLGENBUFFERSPROC)wglGetProcAddress("glGenBuffers");
	glBindBuffer = (PFNGLBINDBUFFERPROC)wglGetProcAddress("glBindBuffer");
	glBufferData = (PFNGLBUFFERDATAPROC)wglGetProcAddress("glBufferData");
	glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)wglGetProcAddress("glDeleteBuffers");

	glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)wglGetProcAddress("glBindVertexArray");
	glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)wglGetProcAddress("glDeleteVertexArrays");
	glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)wglGetProcAddress("glGenVertexArrays");
	glIsVertexArray = (PFNGLISVERTEXARRAYPROC)wglGetProcAddress("glIsVertexArray");

	glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)wglGetProcAddress("glVertexAttribPointer");
	glBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC)wglGetProcAddress("glBindAttribLocation");
	glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glDisableVertexAttribArray");
	glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glEnableVertexAttribArray");

	glGetVertexAttribIuiv = (PFNGLGETVERTEXATTRIBIUIVPROC)wglGetProcAddress("glGetVertexAttribIuiv");
	glIsBuffer = (PFNGLISBUFFERARBPROC)wglGetProcAddress("glIsBuffer");

	isinited_geo = true;
}

image_geo_transform glzMakeIGT(glzIGTType type, unsigned int width, unsigned int height, unsigned int bpp, float x_offset, float y_offset, float z_offset, float scale, float tscale, glzAxis axis, unsigned char *data)
{
	image_geo_transform igt;

	igt.type=type;
	igt.width=width;
	igt.height=height;
	igt.bpp=bpp;
	igt.x_offset=x_offset;
	igt.y_offset=y_offset;
	igt.z_offset=z_offset;
	igt.scale=scale;
	igt.tscale=tscale;
	igt.axis=axis;
	igt.data=data;

	if (igt.width==0) igt.width=1;
	if (igt.height==0) igt.height=1;
	if (igt.scale==0) igt.scale=1.0f;

	return igt;

}


texture_transform glzMakeTT(glzTTType type, float u_scale, float v_scale, float u_offset, float v_offset, unsigned int atlas_width, unsigned int atlas_height, glzAxis axis, unsigned int firstatlas, unsigned int atlas[], glzOrigin origin)
{
	texture_transform tt;

	tt.type=type;
	tt.atlas_width=atlas_width;
	tt.atlas_height=atlas_height;
	tt.u_offset=u_offset;
	tt.v_offset=v_offset;		
	tt.u_scale=u_scale;
	tt.v_scale=v_scale;
	tt.axis=axis;
	tt.firstatlas=firstatlas;
	tt.atlas=atlas;
	tt.origin = origin;

	if (tt.atlas_width==0) tt.atlas_width=1;
	if (tt.atlas_height==0) tt.atlas_height=1;

	return tt;
}


texture_transform glzMakeTTDefault()
{
	return glzMakeTT(glzTTType::NONE, 1.0f, 1.0f, 0.0f, 0.0f, 1, 1, glzAxis::X, 0, 0, glzOrigin::BOTTOM_RIGHT);
}

texture_transform glzMakeTTAtlas(unsigned int awidth, unsigned int aheight, unsigned int firstatlas, glzOrigin origin)
{
	return glzMakeTT(glzTTType::NONE, 1.0f, 1.0f, 0.0f, 0.0f, awidth, aheight, glzAxis::X, firstatlas, 0, origin);
}

texture_transform glzMakeTTAtlasArray(unsigned int awidth, unsigned int aheight, unsigned int atlas[], glzOrigin origin)
{
	return glzMakeTT(glzTTType::ATLASARRAY, 1.0f, 1.0f, 0.0f, 0.0f, awidth, aheight, glzAxis::X, 0, atlas, origin);
}

texture_transform glzMakeTTAtlasCubeTBS(unsigned int awidth, unsigned int aheight, unsigned int firstatlas, glzOrigin origin)
{
	return glzMakeTT(glzTTType::ATLAS_CUBE_TBS, 1.0f, 1.0f, 0.0f, 0.0f, awidth, aheight, glzAxis::X, firstatlas, 0, origin);
}

texture_transform glzMakeTTAtlasCubeIndface(unsigned int awidth, unsigned int aheight, unsigned int firstatlas, glzOrigin origin)
{
	return glzMakeTT(glzTTType::ATLAS_CUBE_INDFACE, 1.0f, 1.0f, 0.0f, 0.0f, awidth, aheight, glzAxis::X, firstatlas, 0, origin);
}

texture_transform glzMakeTTAtlasCubeCross(unsigned int awidth, unsigned int aheight, unsigned int firstatlas, glzOrigin origin)
{
	return glzMakeTT(glzTTType::ATLAS_CUBE_CROSS, 1.0f, 1.0f, 0.0f, 0.0f, awidth, aheight, glzAxis::X, firstatlas, 0, origin);
}

texture_transform glzMakeTTVertexCoordAdopt(float uscale, float vscale, glzAxis axis, glzOrigin origin)
{
	return glzMakeTT(glzTTType::VERTEX_COORD_ADOPT, uscale, vscale, 0.0f, 0.0f, 1, 1, axis, 0, 0, origin);
}

	
primitive_gen glzMakePG(glzPrimitive type, float matrix[16], texture_transform tt, float variation_1, float variation_2, unsigned int resolution_x, unsigned int resolution_y, unsigned int resolution_z)
{
	primitive_gen pg;

	pg.type=type;
	memcpy(pg.matrix,matrix,64);
	pg.tt=tt;
	pg.variation_1=variation_1;
	pg.variation_2=variation_2;		
	pg.resolution_x=resolution_x;
	pg.resolution_y=resolution_y;
	pg.resolution_z=resolution_z;
	return pg;

}

primitive_gen glzMakePGDefault(glzPrimitive type)
{		
	primitive_gen pg;
	pg.type=type;
	glzLoadIdentity(pg.matrix);
	pg.tt=glzMakeTTDefault();
	pg.variation_1=0.0f;
	pg.variation_2=0.0f;		
	pg.resolution_x=1;
	pg.resolution_y=1;
	pg.resolution_z=1;
	return pg;
}

primitive_gen glzMakePGDefaultMatrix(glzPrimitive type, float matrix[16])
{		
	primitive_gen pg;
	pg.type=type;
	memcpy(pg.matrix,matrix,64);
	pg.tt=glzMakeTTDefault();
	pg.variation_1=0.0f;
	pg.variation_2=0.0f;		
	pg.resolution_x=1;
	pg.resolution_y=1;
	pg.resolution_z=1;
	return pg;
}

primitive_gen glzMakePGAtlas(glzPrimitive type, unsigned int awidth, unsigned int aheight, unsigned int firstatlas)
{		
	primitive_gen pg;
	pg.type=type;
	glzLoadIdentity(pg.matrix);
	pg.tt = glzMakeTTAtlas(awidth, aheight, firstatlas, glzOrigin::BOTTOM_RIGHT);
	pg.variation_1=0.0f;
	pg.variation_2=0.0f;		
	pg.resolution_x=1;
	pg.resolution_y=1;
	pg.resolution_z=1;
	return pg;
}

primitive_gen glzMakePGAtlasMatrix(glzPrimitive type, float matrix[16], unsigned int awidth, unsigned int aheight, unsigned int firstatlas)
{		
	primitive_gen pg;
	pg.type=type;
	memcpy(pg.matrix,matrix,64);
	pg.tt = glzMakeTTAtlas(awidth, aheight, firstatlas, glzOrigin::BOTTOM_RIGHT);
	pg.variation_1=0.0f;
	pg.variation_2=0.0f;		
	pg.resolution_x=1;
	pg.resolution_y=1;
	pg.resolution_z=1;
	return pg;
}







void glzIGT(float *vert, image_geo_transform igt, long num)
{
	int i=0,step=igt.bpp;
	float x=0, y=0, z=0;

	switch(igt.type)
	{
	case glzIGTType::DISPLACE_ADD:

		while (i<num)
		{
			// first get coordinate
		x=vert[i*3+0];
		y=vert[i*3+1];
		z=vert[i*3+2];
			
		// offset then scale coordinates

		x+=igt.x_offset;
		y+=igt.y_offset;
		z+=igt.z_offset;

		x*=igt.tscale;
		y*=igt.tscale;
		z*=igt.tscale;

		if (igt.axis == glzAxis::X) vert[i * 3 + 0] += glzImageReadBilinear(y, z, 0, step, igt.width, igt.height, GLZ_REPEAT_X | GLZ_REPEAT_Y, igt.data, true)*igt.scale;

		if (igt.axis == glzAxis::Y) vert[i * 3 + 1] += glzImageReadBilinear(x, z, 0, step, igt.width, igt.height, GLZ_REPEAT_X | GLZ_REPEAT_Y, igt.data, true)*igt.scale;
			
		if (igt.axis == glzAxis::Z) vert[i * 3 + 2] += glzImageReadBilinear(x, y, 0, step, igt.width, igt.height, GLZ_REPEAT_X | GLZ_REPEAT_Y, igt.data, true)*igt.scale;

		i++;
		}


		break;
	default:
		break;

	}


	return;
}


void glzVert2TexcoordRescale(float *vert, float *tex, texture_transform tt, long num)
{
	int i=0;
		while (i<num)
		{

			if (tt.axis == glzAxis::X)
			{
				tex[i*2+0]=(vert[i*3+1])/tt.u_scale;
				tex[i*2+1]=(vert[i*3+2]-1)/tt.v_scale;
			}

			if (tt.axis == glzAxis::Y)
			{
				tex[i*2+0]=(vert[i*3+0])/tt.u_scale;
				tex[i*2+1]=(vert[i*3+2]-1)/tt.v_scale;
			}
			if (tt.axis == glzAxis::Z)
			{
				tex[i*2+0]=(vert[i*3+0])/tt.u_scale;
				tex[i*2+1]=(vert[i*3+1]-1)/tt.v_scale;
			}


		i++;
		}


	return;
}







void glzVAOMakeFromArray(float v[], float t[], float n[], long enteties, unsigned int *vao, glzVAOType type)
{
	if (!isinited_geo) ini_geo();
	
	unsigned int vaopoint;
	vaopoint=*vao;
	if (glIsVertexArray((GLuint)&vao)== GL_FALSE) glzKillVAO(vaopoint,type);

	unsigned int vaotemp;
	unsigned int buffer[3];

	
	glGenVertexArrays(1, &vaotemp);   //generate the vao for this mesh
	glBindVertexArray(vaotemp);

	glGenBuffers( 3, &buffer[0] );	// Get A Valid Name

	glBindBuffer( GL_ARRAY_BUFFER, buffer[0] );			// Bind The Buffer
	glBufferData( GL_ARRAY_BUFFER, enteties*3*sizeof(float), v, GL_DYNAMIC_DRAW);
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	if ((type == glzVAOType::AUTO) || (type == glzVAOType::VERTEX_TEXTURE) || (type == glzVAOType::VERTEX_TEXTURE_NORMAL))
	{
	glBindBuffer( GL_ARRAY_BUFFER, buffer[1] );			// Bind The Buffer
	glBufferData( GL_ARRAY_BUFFER, enteties*2*sizeof(float), t, GL_DYNAMIC_DRAW);
	glVertexAttribPointer((GLuint)1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	}


	if ((type == glzVAOType::AUTO) || (type == glzVAOType::VERTEX_NORMAL) || (type == glzVAOType::VERTEX_TEXTURE_NORMAL))
	{
	glBindBuffer( GL_ARRAY_BUFFER, buffer[2] );			// Bind The Buffer
	glBufferData( GL_ARRAY_BUFFER, enteties*3*sizeof(float), n, GL_DYNAMIC_DRAW);
	glVertexAttribPointer((GLuint)2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	}

	glEnableVertexAttribArray(0);
	if ((type == glzVAOType::AUTO) || (type == glzVAOType::VERTEX_TEXTURE) || (type == glzVAOType::VERTEX_TEXTURE_NORMAL)) glEnableVertexAttribArray(1);
	if ((type == glzVAOType::AUTO) || (type == glzVAOType::VERTEX_NORMAL) || (type == glzVAOType::VERTEX_TEXTURE_NORMAL)) glEnableVertexAttribArray(2);


	glBindVertexArray(0);

	vao[0]=vaotemp;
	addToVaoList(vaotemp);

return;

}



void glzVAOMakeFromVector(vector<poly3> pdata, unsigned int *vao, glzVAOType type)
{
	if (!isinited_geo) ini_geo();

	unsigned int vaopoint;
	vaopoint = *vao;
	if (glIsVertexArray((GLuint)&vao) == GL_FALSE) glzKillVAO(vaopoint, type);

	unsigned int vaotemp;
	unsigned int buffer[3];

	float *v, *t, *n;
	v = new float[pdata.size() * 3 * 3];
	t = new float[pdata.size() * 3 * 2];
	n = new float[pdata.size() * 3 * 3];


	int elements=glzConvertVectorToArray(v, t, n, pdata);



	glGenVertexArrays(1, &vaotemp);   //generate the vao for this mesh
	glBindVertexArray(vaotemp);

	glGenBuffers(3, &buffer[0]);	// Get A Valid Name

	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);			// Bind The Buffer
	glBufferData(GL_ARRAY_BUFFER, elements * 3 * sizeof(float), v, GL_DYNAMIC_DRAW);
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	if ((type == glzVAOType::AUTO) || (type == glzVAOType::VERTEX_TEXTURE) || (type == glzVAOType::VERTEX_TEXTURE_NORMAL))
	{
		glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);			// Bind The Buffer
		glBufferData(GL_ARRAY_BUFFER, elements * 2 * sizeof(float), t, GL_DYNAMIC_DRAW);
		glVertexAttribPointer((GLuint)1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	}


	if ((type == glzVAOType::AUTO) || (type == glzVAOType::VERTEX_NORMAL) || (type == glzVAOType::VERTEX_TEXTURE_NORMAL))
	{
		glBindBuffer(GL_ARRAY_BUFFER, buffer[2]);			// Bind The Buffer
		glBufferData(GL_ARRAY_BUFFER, elements * 3 * sizeof(float), n, GL_DYNAMIC_DRAW);
		glVertexAttribPointer((GLuint)2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	}

	glEnableVertexAttribArray(0);
	if ((type == glzVAOType::AUTO) || (type == glzVAOType::VERTEX_TEXTURE) || (type == glzVAOType::VERTEX_TEXTURE_NORMAL)) glEnableVertexAttribArray(1);
	if ((type == glzVAOType::AUTO) || (type == glzVAOType::VERTEX_NORMAL) || (type == glzVAOType::VERTEX_TEXTURE_NORMAL)) glEnableVertexAttribArray(2);


	glBindVertexArray(0);

	vao[0] = vaotemp;
	addToVaoList(vaotemp);


	delete[] v;
	delete[] t;
	delete[] n;
	v = NULL;
	t = NULL;
	n = NULL;


	return;

}



long glzConvertVectorToArray(float *v, float *t, float *n, vector<poly3> pdata)
{

	int i = 0;

	for (auto p : pdata)
	{

		v[i * 3 * 3 + 0] = p.a.v.x;
		v[i * 3 * 3 + 1] = p.a.v.y;
		v[i * 3 * 3 + 2] = p.a.v.z;

		t[i * 2 * 3 + 0] = p.a.t.u;
		t[i * 2 * 3 + 1] = p.a.t.v;

		n[i * 3 * 3 + 0] = p.a.n.x;
		n[i * 3 * 3 + 1] = p.a.n.y;
		n[i * 3 * 3 + 2] = p.a.n.z;

		v[i * 3 * 3 + 3] = p.b.v.x;
		v[i * 3 * 3 + 4] = p.b.v.y;
		v[i * 3 * 3 + 5] = p.b.v.z;

		t[i * 2 * 3 + 2] = p.b.t.u;
		t[i * 2 * 3 + 3] = p.b.t.v;

		n[i * 3 * 3 + 3] = p.b.n.x;
		n[i * 3 * 3 + 4] = p.b.n.y;
		n[i * 3 * 3 + 5] = p.b.n.z;

		v[i * 3 * 3 + 6] = p.c.v.x;
		v[i * 3 * 3 + 7] = p.c.v.y;
		v[i * 3 * 3 + 8] = p.c.v.z;

		t[i * 2 * 3 + 4] = p.c.t.u;
		t[i * 2 * 3 + 5] = p.c.t.v;

		n[i * 3 * 3 + 6] = p.c.n.x;
		n[i * 3 * 3 + 7] = p.c.n.y;
		n[i * 3 * 3 + 8] = p.c.n.z;

		i++;
	}


	return (i * 3);
}


void glzDirectPointArrayRender(float v[], float t[], int E)
{

	unsigned int localVAO;


	float n[] = {0.0f, 0.0f, 1.0f};
		glzVAOMakeFromArray(v, t, n, E, &localVAO, glzVAOType::VERTEX_TEXTURE);


	glzDrawVAO(0, E, localVAO, GL_POINTS);
	glzKillVAO(localVAO, glzVAOType::VERTEX_TEXTURE);

	return;
}


void glzDirectCubeRender(float X, float Y, float Z, float W, float H, float D, texture_transform tt, unsigned int atlas)
{
	if (!isinited_geo) ini_geo();

	unsigned int localVAO;

	float v[36 * 3], t[36 * 2], n[36 * 3];

	float m[16];
	glzLoadIdentity(m);
	glzScalef(m, W,H,D);


	glzPrimCubeverts(v, t, n);

	glzAtlasUVarrayRemap(atlas, 36, tt.atlas_width, tt.atlas_height, tt.origin, t);
	glzProjectVertexArray(v, m, 36);

	glzVAOMakeFromArray(v, t, n, 36, &localVAO, glzVAOType::AUTO);
	
	
	glzDrawVAO(0, 36, localVAO, GL_TRIANGLES);
	glzKillVAO(localVAO, glzVAOType::AUTO);


	return;
}




void glzKillVAO(unsigned int vao, glzVAOType type)
{
	if (!isinited_geo) ini_geo();
	if (!glIsVertexArray(vao)) return; // is this a vao

	removeFromVaoList(vao);

	glBindVertexArray(vao);

	unsigned int vbuf;
	glGetVertexAttribIuiv(0,GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING,&vbuf);
	if( glIsBuffer(vbuf)) glDeleteBuffers(1,&vbuf);

	if ((type == glzVAOType::AUTO) || (type == glzVAOType::VERTEX) || (type == glzVAOType::VERTEX_TEXTURE))
	{
	glGetVertexAttribIuiv(1,GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING,&vbuf);
	if( glIsBuffer(vbuf))  glDeleteBuffers(1,&vbuf);
	}

	if ((type == glzVAOType::AUTO) || (type == glzVAOType::VERTEX) || (type == glzVAOType::VERTEX_NORMAL) || (type == glzVAOType::VERTEX_TEXTURE_NORMAL))
	{
	glGetVertexAttribIuiv(2,GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING,&vbuf);
	if( glIsBuffer(vbuf))  glDeleteBuffers(1,&vbuf);
	}


	glDeleteVertexArrays(1,reinterpret_cast<GLuint *>(&vao));
	glBindVertexArray(0);

	return;
}


void glzKillAllVAO(void)
{
	if (!isinited_geo) ini_geo();
	int i=0;

	while (i<1024)
	{
		//if(active_vao[i]!=-1)
		glzKillVAO(active_vao[i], glzVAOType::AUTO);
		i++;
	}

	return;
}


void glzDrawVAO(long enteties, unsigned int vao, unsigned int type)
{
	if (!isinited_geo) ini_geo();

	glBindVertexArray(vao);
	glDrawArrays(type, 0, enteties);
	glBindVertexArray(0);
	return;
}


void glzDrawVAO(long offset, long enteties, unsigned int vao, unsigned int type)
{
	if (!isinited_geo) ini_geo();

	glBindVertexArray(vao);
	glDrawArrays(type, offset, enteties);
	glBindVertexArray(0);
	return;
}


// there are a lot of things i like to add here and if it becomes to mcuh i might split it up into 3 files
// one for generated geometry, loaded geometry and other stuff.
// if you have some fun geometry generation to add then look at glzVAOMakeHeightAtlasGrid since it will be more or less how all of them will look like once i expand
// the image geo transform to work on everything
