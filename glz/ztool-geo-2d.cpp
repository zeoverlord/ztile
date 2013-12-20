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

// glz geometry toolkit 2d- for allmost all your 2d geometry needs
// visit http://www.flashbang.se or contact me at overlord@flashbang.se
// the entire toolkit should exist in it's entirety at github
// https://github.com/zeoverlord/glz.git


#include <fstream>
#include <math.h>
#include <string.h>
#include "ztool-glz.h"
#include "ztool-geo.h"
#include "ztool-geo-2d.h"
#include <stdio.h>
#include <windows.h>													// Header File For The Windows Library
#include <gl/gl.h>														// Header File For The OpenGL32 Library
#include <gl/glu.h>														// Header File For The GLu32 Library
#include <gl/glext.h>

using namespace std;



static bool isinited;

void ini(void)
{


	isinited = true;
}


// direct rendering functions for sprites and such, mostly 2D stuff

void glzDirectSpriteRender(float X, float Y, float Z, float W, float H, float spriteX, float spriteY, float spriteW, float spriteH, glzOrigin orientation)
{

	unsigned int localVAO;


	float vc[] = {
		X - W*0.5f, Y - H*0.5f, Z,
		X + W*0.5f, Y - H*0.5f, Z,
		X + W*0.5f, Y + H*0.5f, Z,
		X - W*0.5f, Y + H*0.5f, Z,
		X - W*0.5f, Y - H*0.5f, Z,
		X + W*0.5f, Y + H*0.5f, Z };

	float vtr[] = {
		X - W, Y - H, Z,
		X, Y - H, Z,
		X, Y, Z,
		X - W, Y, Z,
		X - W, Y - H, Z,
		X, Y, Z };

	float vbr[] = {
		X - W, Y, Z,
		X, Y, Z,
		X, Y + H, Z,
		X - W, Y + H, Z,
		X - W, Y, Z,
		X, Y + H, Z };

	float vtl[] = {
		X, Y - H, Z,
		X + W, Y - H, Z,
		X + W, Y, Z,
		X, Y, Z,
		X, Y - H, Z,
		X + W, Y, Z };

	float vbl[] = {
		X, Y, Z,
		X + W, Y, Z,
		X + W, Y + H, Z,
		X, Y + H, Z,
		X, Y, Z,
		X + W, Y + H, Z };

	float t[] = {
		spriteX, spriteY,
		spriteX + spriteW, spriteY,
		spriteX + spriteW, spriteY + spriteH,
		spriteX, spriteY + spriteH,
		spriteX, spriteY,
		spriteX + spriteW, spriteY + spriteH };

	float n[] = {
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f };

	switch (orientation)
	{


	case glzOrigin::CENTERED:
		glzVAOMakeFromArray(vc, t, n, 6, &localVAO, glzVAOType::AUTO);
		break;

	case glzOrigin::TOP_RIGHT:
		glzVAOMakeFromArray(vtr, t, n, 6, &localVAO, glzVAOType::AUTO);
		break;

	case glzOrigin::BOTTOM_RIGHT:
		glzVAOMakeFromArray(vbr, t, n, 6, &localVAO, glzVAOType::AUTO);
		break;

	case glzOrigin::TOP_LEFT:
		glzVAOMakeFromArray(vtl, t, n, 6, &localVAO, glzVAOType::AUTO);
		break;

	case glzOrigin::BOTTOM_LEFT:
	default:
		glzVAOMakeFromArray(vbl, t, n, 6, &localVAO, glzVAOType::AUTO);
		break;

	}
	glzDrawVAO(0, 6, localVAO, GL_TRIANGLES);
	glzKillVAO(localVAO, glzVAOType::AUTO);

	return;
}


void glzDirectSpriteRenderAtlas(float X, float Y, float Z, float W, float H, unsigned int atlasW, unsigned int atlasH, unsigned int atlasN, glzOrigin orientation)
{

	float quv[8];
	glzAtlasQuad(atlasW, atlasH, atlasN, orientation, quv);
	glzDirectSpriteRender(X, Y, Z, W, H, quv[2], quv[3], quv[6] - quv[2], quv[7] - quv[3], orientation);

	return;
}

void glzDirectSpriteRenderAtlasPixelPerfect(float X, float Y, float Z, int textureW, int textureH, unsigned int atlasW, unsigned int atlasH, unsigned int atlasN, glzOrigin orientation)
{

	glzDirectSpriteRenderAtlas(X, Y, Z, (float)textureW / (float)atlasW, (float)textureH / (float)atlasH, atlasW, atlasH, atlasN, orientation);

	return;
}

void glzDirectSpriteRenderAtlasPixelPerfectQuantized(float X, float Y, float Z, int textureW, int textureH, unsigned int atlasW, unsigned int atlasH, unsigned int atlasN, float q, glzOrigin orientation)
{

	glzDirectSpriteRenderAtlas(quantize(X, q), quantize(Y, q), Z, (float)textureW / (float)atlasW, (float)textureH / (float)atlasH, atlasW, atlasH, atlasN, orientation);

	return;
}