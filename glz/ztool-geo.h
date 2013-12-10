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

#include "ztool-type.h"



typedef struct Point2Struct {
	double x, y;
} Point2;

typedef struct Point3Struct {
	double x, y, z;
} Point3;


typedef struct
	{
		glzIGTType type;
		unsigned int width;
		unsigned int height;
		unsigned int bpp;
		float x_offset;
		float y_offset;
		float z_offset;
		float scale;
		float tscale;
		glzAxis axis;
		unsigned char *data;
	} image_geo_transform;

typedef struct
	{
		glzTTType type;
		float u_scale;
		float v_scale;
		float u_offset;
		float v_offset;
		unsigned int atlas_width;
		unsigned int atlas_height;		
		glzAxis axis;
		unsigned int firstatlas;
		unsigned int *atlas;
		glzOrigin origin;
	} texture_transform;

typedef struct
	{
		glzPrimitive type;
		float matrix[16];
		texture_transform tt;
		float variation_1;
		float variation_2;
		unsigned int resolution_x;
		unsigned int resolution_y;
		unsigned int resolution_z;

	} primitive_gen;




		//type signifies the type of data to choose from, if set at GLZ_AUTO it chooses the default settings
		//vao always returns the created VAO
		//every function that creates a VAO returns the amount of Vertics to output
		// every VAO funtion resets the vao to 0 to prevent problems unless otherwise specified


image_geo_transform glzMakeIGT(glzIGTType type, unsigned int width, unsigned int height, unsigned int bpp, float x_offset, float y_offset, float z_offset, float scale, float tscale, glzAxis axis, unsigned char *data);
	
texture_transform glzMakeTT(glzTTType type, float u_scale, float v_scale, float u_offset, float v_offset, unsigned int atlas_width, unsigned int atlas_height, glzAxis axis, unsigned int firstatlas, unsigned int atlas[], glzOrigin origin);
	texture_transform glzMakeTTDefault();
	texture_transform glzMakeTTAtlas(unsigned int awidth, unsigned int aheight, unsigned int firstatlas, glzOrigin origin);
	texture_transform glzMakeTTAtlasArray(unsigned int awidth, unsigned int aheight, unsigned int atlas[], glzOrigin origin);
	texture_transform glzMakeTTAtlasCubeTBS(unsigned int awidth, unsigned int aheight, unsigned int firstatlas, glzOrigin origin);
	texture_transform glzMakeTTAtlasCubeIndface(unsigned int awidth, unsigned int aheight, unsigned int firstatlas, glzOrigin origin);
	texture_transform glzMakeTTAtlasCubeCross(unsigned int awidth, unsigned int aheight, unsigned int firstatlas, glzOrigin origin);
	texture_transform glzMakeTTVertexCoordAdopt(float uscale, float vscale, glzAxis axis, glzOrigin origin);

	primitive_gen glzMakePG(glzPrimitive type, float matrix[16], texture_transform tt, float variation_1, float variation_2, unsigned int resolution_x, unsigned int resolution_y, unsigned int resolution_z);
	primitive_gen glzMakePGDefault(glzPrimitive type);
	primitive_gen glzMakePGDefaultMatrix(glzPrimitive type, float matrix[16]);
	primitive_gen glzMakePGAtlas(glzPrimitive type, unsigned int awidth, unsigned int aheight, unsigned int firstatlas);
	primitive_gen glzMakePGAtlasMatrix(glzPrimitive type, float matrix[16], unsigned int awidth, unsigned int aheight, unsigned int firstatlas);

	
	long glzVAOMakeFromFile(char filename[255], float matrix[], texture_transform tt, unsigned int *vao);
	void glzVAOMakeFromArray(float v[], float t[], float n[], long enteties, unsigned int *vao, glzVAOType type);

	long glzVAOMakeText(char text[255], float matrix[], float kern, texture_transform tt, unsigned int *vao);
	
	long glzVAOMakeAtlasGrid(unsigned int x, unsigned int y, float matrix[], texture_transform tt, unsigned int *vao);	
	long glzVAOMakeHeightAtlasGrid(unsigned int x, unsigned int y, float matrix[], texture_transform tt, image_geo_transform igt, unsigned int *vao);

	long glzVAOCountPrimitiveVerts(float varation, float resuloution, unsigned int primitive, texture_transform tt);
	long glzVAOMakePrimitive(primitive_gen pg, unsigned int *vao);
	long glzVAOMakePrimitives(int num, primitive_gen pg[], unsigned int *vao);

	void glzDirectSpriteRender(float X, float Y, float Z, float W, float H, float spriteX, float spriteY, float spriteW, float spriteH, glzOrigin orientation);  // mirroring GL_DrawTextureNV somewhat
	void glzDirectSpriteRenderAtlas(float X, float Y, float Z, float W, float H, unsigned int atlasW, unsigned int atlasH, unsigned int atlasN, glzOrigin orientation);
	void glzDirectSpriteRenderAtlasPixelPerfect(float X, float Y, float Z, int textureW, int textureH, unsigned int atlasW, unsigned int atlasH, unsigned int atlasN, glzOrigin orientation);
	void glzDirectSpriteRenderAtlasPixelPerfectQuantized(float X, float Y, float Z, int textureW, int textureH, unsigned int atlasW, unsigned int atlasH, unsigned int atlasN, float q, glzOrigin orientation);


	void glzKillVAO(unsigned int vao, glzVAOType type);
	void glzKillAllVAO(void);

	void glzDrawVAO(long enteties, unsigned int vao, unsigned int type);
	void glzDrawVAO(long offset, long enteties, unsigned int vao, unsigned int type);


	/* 
	not implemented, is subject to change

	// these two will output to a .vao file for later loading with glzVAOMakeFromFile, it will save the buffers and the vertexatrib indices as they are in the VAO, though not the names
	glzVAOsave(char filename[255], long enteties, unsigned int vao[], unsigned int type);
	glzVAOsaveRange(char filename[255], long offset, long enteties, unsigned int vao[], unsigned int type); 
	
	*/







