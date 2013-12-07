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

// glz toolkit - this file contains may usefull little functions and many more useless ones
// visit http://www.flashbang.se or contact me at overlord@flashbang.se
// the entire toolkit should exist in it's entirety at github
// https://github.com/zeoverlord/glz.git

#define GLZ_NULL 0

#define GLZ_AUTO 0
#define GLZ_VERTEX 1
#define GLZ_VERTEX_TEXTURE 2
#define GLZ_VERTEX_NORMAL 4

#define GLZ_INVERT 1

#define GLZ_BOTTOM_LEFT 1
#define GLZ_BOTTOM_RIGHT 2
#define GLZ_TOP_LEFT 4
#define GLZ_TOP_RIGHT 8

#define GLZ_MIRROR_X 1
#define GLZ_MIRROR_Y 2
#define GLZ_REPEAT_X 4
#define GLZ_REPEAT_Y 8
#define GLZ_CLAMP_X 16
#define GLZ_CLAMP_Y 32


// color channels

#define GLZ_RED 0
#define GLZ_GREEN 1
#define GLZ_BLUE 2
#define GLZ_ALPHA 3

#define GLZ_HUE 4
#define GLZ_HUE2 5
#define GLZ_CROMA 6
#define GLZ_CROMA2 7
#define GLZ_VALUE 8
#define GLZ_LIGHTNESS 9
#define GLZ_INTENSITY 10
#define GLZ_LUMA 11
#define GLZ_SHSV 12
#define GLZ_SHSL  13
#define GLZ_SHSI 14


#define GLZ_RGB 3
#define GLZ_RGBA 4


// color conversion


#define GLZ_RGB_8 1
#define GLZ_RGB_32F 2

#define GLZ_RGBA_8 32
#define GLZ_RGBA_32F 4

#define GLZ_HSL_8 5
#define GLZ_HSL_32F 6

#define GLZ_HSV_8 7
#define GLZ_HSV_32F 8

#define GLZ_HSI_8 9
#define GLZ_HSI_32F 10


#define GLZ_HCY_8 11
#define GLZ_HCY_32F 12





#define PI				3.1415926535897932384626433832795
#define PI_OVER_180		0.017453292519943295769236907684886
#define PI_OVER_360		0.0087266462599716478846184538424431
#define PI_OVER_180_REVERSE		57.2957795131



		//type signifies the type of data to choose from, if set at GLZ_AUTO it chooses the default settings



// usefull stuff

float glzRandf(void);  //produces a value between 1 and 0
float glzRandfs(void);  //produces a value between 1 and -1

float glzModF(float f, float m);  //float modulo function
int glzModFStep(float f, float m);  //special float modulo function that returns the number of times m fits in f
int glzTimeCounter(float *t, float m);  //timing function
float quantize(float f, float s); //quantized steping formula


// some general math functions


float glzDotproductf(float a[3], float b[3]);
double glzDotproductd(double a[3], double b[3]);
float glzMagnitudef(float a[3]);
double glzMagnituded(double a[3]);
void glzNormalizef(float *a, float le); //le is the length to normalizr to, normaly should be left at 1.0
void glzNormalized(double *a, double le);
void glzCrossproductf(float a[3], float b[3], float *r);
void glzCrossproductd(double a[3], double b[3], double *r);


// image functions

unsigned int glz2dTo1dImageRemap(unsigned int x, unsigned int y, unsigned int col, unsigned int step, unsigned int width, unsigned int height, unsigned int type);
float glzImageReadBilinear(float x, float y, unsigned int col, unsigned int step, int width, int height, unsigned int mirror, unsigned char *data, unsigned int type);

float glzColorConvert(float a, float b, float c, unsigned int intype, unsigned int outtype);

// specialty code

float glzRemapToRange(float curmin,float cur,float curmax, float rmin, float rmax);
void glzRemapToRangeArray(float curmin,float curmax, float rmin, float rmax, float *curdata, unsigned int num);
void glzCubicCurve(float pos, float l, float p1[3], float v1[3], float p2[3], float v2[3], float *ret);
void glzAtlasQuad(unsigned int xres, unsigned int yres, unsigned int atlas, float *uvOut);
void glzAtlasAniQuad(unsigned int xres, unsigned int yres, float time, float *uvout);
void glzAtlasUVarrayRemap(unsigned int atlas,unsigned int num,unsigned int aw,unsigned int ah, float *uv);
void glzAtlasUVarrayRemapRotate(unsigned int r,unsigned int atlas, unsigned int num,unsigned int aw,unsigned int ah, float *uv);


// matrix stuff

void glzProjectVertex(float  *vert, float Matrix[16]);
void glzProjectVertexArray(float  *vert, float Matrix[16], int num);
void glzMultMatrix(float *MatrixB,float  MatrixA[16]);
void glzLoadIdentity(float *m);
void glzPerspective(float *m, float fov, float aspect,float zNear, float zFar);
void glzOrtho(float *m, float left, float right, float bottom, float top, float Znear, float Zfar);
void glzTranslatef(float *m,float x,float y, float z);
void glzScalef(float *m,float x,float y, float z);
void glzRotatef(float *m, float a, float x,float y, float z);

// Quaternion stuff
void glzLoadQuaternionIdentity(float *q);
void glzMultQuaternion(float *qa, float qb[4]);
void glzNormalizeQuaternion(float *q);
void glzRotateQuaternionf(float *q, float a, float x,float y, float z);
void glzQuaternionToMatrixf(float *m, float q[4]);


// 2D colisions
unsigned int glzPhys2DColideBox2(float x1,float y1,float r1, float x2,float y2,float r2);








