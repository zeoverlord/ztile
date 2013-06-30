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

// glz texture toolkit - will load any image in the world as long as it's a small subset of the .tga format
// visit http://www.flashbang.se or contact me at overlord@flashbang.se
// the entire toolkit should exist in it's entirety at github
// https://github.com/zeoverlord/glz.git

#define GLZ_AUTO 0
#define GLZ_UNCOMPRESSED 1
#define GLZ_COMPRESSED 2



#define GLZ_FILTER_NONE			0x0010
#define GLZ_FILTER_NEAREST		0x0011
#define GLZ_FILTER_LINEAR		0x0012
#define GLZ_FILTER_BILINEAR		0x0013
#define GLZ_FILTER_TRILINEAR	0x0014
#define GLZ_FILTER_ANSIO_2		0x0015
#define GLZ_FILTER_ANSIO_4		0x0016
#define GLZ_FILTER_ANSIO_8		0x0017
#define GLZ_FILTER_ANSIO_16		0x0018
#define GLZ_FILTER_ANSIO_MAX	0x0019


#define GLZ_BOTTOM_LEFT 1
#define GLZ_BOTTOM_RIGHT 2
#define GLZ_TOP_LEFT 4
#define GLZ_TOP_RIGHT 8



typedef struct
	{
	unsigned int m_width;
	unsigned int m_height;
	unsigned int m_bpp;
	unsigned int m_id;
	unsigned int m_type;
	long imageSize;
	unsigned int orientation;
	} img_head;


//type signifies the type of data to choose from, if set at GLZ_AUTO it chooses the default settings



//loading

// segmented loading, for if you want to load a texture into the cpu
void glzReadTgaHead(img_head *img,char filename[255]);
void glzLoadTga(img_head *img,char filename[255], unsigned char *data);
void glzMaketex(img_head *img, unsigned char data[], unsigned int filter);

unsigned int glzLoadTexture(char filename[255], unsigned int filter);  // type is here which image type (same as in openGL) and filter is the texture filtering
// this load function only loads either TGA files or whtever the file ending is, but that's for another version


// saving


void glzScreenShot(char filename[255],int x, int y, unsigned int type);  // auto saves a compressed file
void glzScreenShotADV(char filename[255],int xoffset, int yoffset, int x, int y, int lossy, unsigned int type);


/*
// future stuff

* multiple save formats
* Multiple load formats bmp, openEXR, GTF(my own format) and maybe others
* better image preprocessing (for cubemaps and so on)
* subtexture loading, using chunks for megatextures
* procedural texture generation, also megatexture capable
* some FBO management

*/








