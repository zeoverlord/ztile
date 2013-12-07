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

#define GLZ_AUTO 0
#define GLZ_VERTEX 1
#define GLZ_TEXTURE 2
#define GLZ_NORMAL 4

// primitives, note that not all of these are implemented
#define GLZ_PRIMITIVE_CUBE 0x001
#define GLZ_PRIMITIVE_SPHERE 0x002 // not implemented
#define GLZ_PRIMITIVE_PYRAMID 0x003 
#define GLZ_PRIMITIVE_TETRAHEDRON 0x004
#define GLZ_PRIMITIVE_HEXAHEDRON 0x001
#define GLZ_PRIMITIVE_OCTAHEDRON 0x005 
#define GLZ_PRIMITIVE_DODECAHEDRON 0x006 
#define GLZ_PRIMITIVE_ICOSAHEDRON 0x007 
#define GLZ_PRIMITIVE_ICOSIDODECAHEDRON 0x008 
#define GLZ_PRIMITIVE_TORUS 0x009 // not implemented
// geodesics, as in they are subdivided, a resolution_x of 1 is equal to 1 subdivision, 
// if 0 then they are the same as their originating objects
#define GLZ_PRIMITIVE_GEODESIC_TETRA 0x101 // not implemented
#define GLZ_PRIMITIVE_GEODESIC_HEXA 0x102 // not implemented
#define GLZ_PRIMITIVE_GEODESIC_OCTA 0x103 // not implemented
#define GLZ_PRIMITIVE_GEODESIC_DODECA 0x104 // not implemented
#define GLZ_PRIMITIVE_GEODESIC_ICOSA 0x105 // not implemented
// closed, other primitives
#define GLZ_PRIMITIVE_DOME 0x201 // not implemented
#define GLZ_PRIMITIVE_DISC 0x202 // not implemented
#define GLZ_PRIMITIVE_STAR_DODECAHEDRON 0x203 // not implemented

// various other structures
#define GLZ_PRIMITIVE_FSQ 0x301
#define GLZ_PRIMITIVE_RANDOM_POINT 0x302
#define GLZ_PRIMITIVE_SPRITE_ATLAS_ARRAY 0x303

#define GLZ_AXIS_X 1
#define GLZ_AXIS_Y 2
#define GLZ_AXIS_Z 4

// igt types

#define GLZ_IGT_NONE 0
#define GLZ_IGT_DISPLACE_ADD 1


#define GLZ_TT_NONE 0
#define GLZ_TT_VERTEX_COORD_ADOPT 1
#define GLZ_TT_ATLASARRAY 2
#define GLZ_TT_ATLAS_CUBE_TBS 3
#define GLZ_TT_ATLAS_CUBE_INDFACE 4
#define GLZ_TT_ATLAS_CUBE_CROSS 5

#define GLZ_BOTTOM_LEFT 1
#define GLZ_BOTTOM_RIGHT 2
#define GLZ_TOP_LEFT 4
#define GLZ_TOP_RIGHT 8




typedef struct Point2Struct {
	double x, y;
} Point2;

typedef struct Point3Struct {
	double x, y, z;
} Point3;


typedef struct
	{
		unsigned int type;
		unsigned int width;
		unsigned int height;
		unsigned int bpp;
		float x_offset;
		float y_offset;
		float z_offset;
		float scale;
		float tscale;
		unsigned int axis;
		unsigned char *data;
	} image_geo_transform;

typedef struct
	{
		unsigned int type;
		float u_scale;
		float v_scale;
		float u_offset;
		float v_offset;
		unsigned int atlas_width;
		unsigned int atlas_height;		
		unsigned int axis;
		unsigned int firstatlas;
		unsigned int *atlas;
	} texture_transform;

typedef struct
	{
		unsigned int type;
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


	image_geo_transform glzMakeIGT(unsigned int type, unsigned int width, unsigned int height, unsigned int bpp, float x_offset, float y_offset, float z_offset, float scale, float tscale, unsigned int axis, unsigned char *data);
	
	texture_transform glzMakeTT(unsigned int type, float u_scale, float v_scale, float u_offset, float v_offset, unsigned int atlas_width, unsigned int atlas_height, unsigned int axis, unsigned int firstatlas,  unsigned int atlas[]);
	texture_transform glzMakeTTDefault();
	texture_transform glzMakeTTAtlas(unsigned int awidth, unsigned int aheight, unsigned int firstatlas);
	texture_transform glzMakeTTAtlasArray(unsigned int awidth, unsigned int aheight, unsigned int atlas[]);
	texture_transform glzMakeTTAtlasCubeTBS(unsigned int awidth, unsigned int aheight, unsigned int firstatlas);
	texture_transform glzMakeTTAtlasCubeIndface(unsigned int awidth, unsigned int aheight, unsigned int firstatlas);
	texture_transform glzMakeTTAtlasCubeCross(unsigned int awidth, unsigned int aheight, unsigned int firstatlas);
	texture_transform glzMakeTTVertexCoordAdopt(float uscale, float vscale, unsigned int axis);

	primitive_gen glzMakePG(unsigned int type, float matrix[16], texture_transform tt, float variation_1, float variation_2, unsigned int resolution_x, unsigned int resolution_y, unsigned int resolution_z);
	primitive_gen glzMakePGDefault(unsigned int type);
	primitive_gen glzMakePGDefaultMatrix(unsigned int type, float matrix[16]);	
	primitive_gen glzMakePGAtlas(unsigned int type, unsigned int awidth, unsigned int aheight, unsigned int firstatlas);
	primitive_gen glzMakePGAtlasMatrix(unsigned int type, float matrix[16], unsigned int awidth, unsigned int aheight, unsigned int firstatlas);

	
	long glzVAOMakeFromFile(char filename[255], float matrix[], texture_transform tt, unsigned int *vao);
	void glzVAOMakeFromArray(float v[], float t[], float n[], long enteties, unsigned int *vao,unsigned int type);

	long glzVAOMakeText(char text[255], float matrix[], float kern, texture_transform tt, unsigned int *vao);
	
	long glzVAOMakeAtlasGrid(unsigned int x, unsigned int y, float matrix[], texture_transform tt, unsigned int *vao);	
	long glzVAOMakeHeightAtlasGrid(unsigned int x, unsigned int y, float matrix[], texture_transform tt, image_geo_transform igt, unsigned int *vao);

	long glzVAOCountPrimitiveVerts(float varation, float resuloution, unsigned int primitive, texture_transform tt);
	long glzVAOMakePrimitive(primitive_gen pg, unsigned int *vao);
	long glzVAOMakePrimitives(int num, primitive_gen pg[], unsigned int *vao);

	void glzDirectSpriteRender(float X, float Y, float Z, float W, float H, float spriteX, float spriteY, float spriteW, float spriteH, unsigned int orientation);  // mirroring GL_DrawTextureNV somewhat
	void glzDirectSpriteRenderAtlas(float X, float Y, float Z, float W, float H, unsigned int atlasW, unsigned int atlasH, unsigned int atlasN, unsigned int orientation);  
	void glzDirectSpriteRenderAtlasPixelPerfect(float X, float Y, float Z, int textureW, int textureH, unsigned int atlasW, unsigned int atlasH, unsigned int atlasN, unsigned int orientation);
	void glzDirectSpriteRenderAtlasPixelPerfectQuantized(float X, float Y, float Z, int textureW, int textureH, unsigned int atlasW, unsigned int atlasH, unsigned int atlasN, float q, unsigned int orientation);


	void glzKillVAO(unsigned int vao, unsigned int type);
	void glzKillAllVAO(void);

	void glzDrawVAO(long enteties, unsigned int vao, unsigned int type);
	void glzDrawVAO(long offset, long enteties, unsigned int vao, unsigned int type);


	/* 
	not implemented, is subject to change

	// these two will output to a .vao file for later loading with glzVAOMakeFromFile, it will save the buffers and the vertexatrib indices as they are in the VAO, though not the names
	glzVAOsave(char filename[255], long enteties, unsigned int vao[], unsigned int type);
	glzVAOsaveRange(char filename[255], long offset, long enteties, unsigned int vao[], unsigned int type); 
	
	*/







