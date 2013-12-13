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

#include "primitives.h"
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


static bool isinited;
static int active_vao[1024];

// most of the functions below are booring stuff and will not be commented on as they are pretty mic self explanatory
// it's mostly just setting up primitives, generating geometry and setting up structures
// but if you like to make your own primitive there are two easy ways, either copy the arrays in primitives.h or set something up like the below function glzPrimCubeverts


long glzPrimCubeverts(float *v,float *t,float *n)
{
		float vt[] =
{	 	
	-0.5f,  0.5f, -0.5f, //top
	-0.5f,  0.5f,  0.5f, 
	 0.5f,  0.5f,  0.5f, 
	 0.5f,  0.5f, -0.5f, 
	-0.5f,  0.5f, -0.5f, 
	 0.5f,  0.5f,  0.5f,

	-0.5f, -0.5f, -0.5f, // bottom
	 0.5f, -0.5f, -0.5f, 
	 0.5f, -0.5f,  0.5f, 
	-0.5f, -0.5f,  0.5f, 
	-0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f,  0.5f,
	 
	-0.5f, -0.5f,  0.5f, // front
	 0.5f, -0.5f,  0.5f, 
	 0.5f,  0.5f,  0.5f, 
	-0.5f,  0.5f,  0.5f, 
	-0.5f, -0.5f,  0.5f,
	 0.5f,  0.5f,  0.5f,

	0.5f, -0.5f, -0.5f, // right
	 0.5f,  0.5f, -0.5f,
	 0.5f,  0.5f,  0.5f, 
	 0.5f, -0.5f,  0.5f, 
	 0.5f, -0.5f, -0.5f,
	 0.5f,  0.5f,  0.5f,

	-0.5f, -0.5f, -0.5f, // back
	-0.5f,  0.5f, -0.5f, 
	 0.5f,  0.5f, -0.5f, 
	 0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	 0.5f,  0.5f, -0.5f, 

	 -0.5f, -0.5f, -0.5f, // left
	-0.5f, -0.5f,  0.5f, 
	-0.5f,  0.5f,  0.5f, 
	-0.5f,  0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f,  0.5f,  0.5f
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

	memcpy(v,vt,36*3*4);
	memcpy(t,tt,36*2*4);
	memcpy(n,nt,36*3*4);

	return 36;
}



long glzPrimFSQ(float *v,float *t,float *n)
{
float vt[] ={
	-1.0f, -1.0f,  1.0f, 
	 1.0f, -1.0f,  1.0f, 
	 1.0f,  1.0f,  1.0f, 
	-1.0f,  1.0f,  1.0f, 
	-1.0f, -1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f};

	float tt[] ={
	0.0f, 0.0f, 
	1.0f, 0.0f, 
	1.0f, 1.0f, 
	0.0f, 1.0f,
	0.0f, 0.0f, 
	1.0f, 1.0f};

	// + or - 0.0025f is to adjust the texture coords for full screen viewingso to reduce edge bleeding, though it might have to be adjusted for later, this is for 800x600, i think

	float nt[] ={
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,	
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f};


	memcpy(v,vt,6*3*4);
	memcpy(t,tt,6*2*4);
	memcpy(n,nt,6*3*4);


	return 6;
}

long glzPrimRandom(float *v,float *t,float *n, int num)
{
	int i=0;
	float nt[3];

	for(i=0; i<num*3; i++)
	{
		v[i]=glzRandfs()*0.5f;
	}
		
	for(i=0; i<num*2; i++)
	{
		t[i]=glzRandf();
	}

	for(i=0; i<num*3; i+=3)
	{		
		nt[0]=glzRandfs();
		nt[1]=glzRandfs();
		nt[2]=glzRandfs();
		glzNormalizef(&nt[0],1.0f);
		n[i+0]=nt[0];
		n[i+1]=nt[1];
		n[i+2]=nt[2];
	}

	return (long)num;
}

long glzPrimTetra(float *v,float *t,float *n)
{


	float p1[3]={0,-0.5f,(sqrt(3.0f)-(1/sqrt(3.0f)))*0.5f};
    float p2[3]={0.5,-0.5f,-0.5f/sqrt(3.0f)};
    float p3[3]={-0.5,-0.5f,-0.5f/sqrt(3.0f)};
    float p4[3]={0,1*sqrt(2.0f/3.0f)-0.5f,0};

	float t1[2]={ 0, 0};
	float t2[2]={ 0, 1};
	float t3[2]={ 1, 1};
	float t4[2]={ 1, 0};
	float t5[2]={ 0.5, 0.5};

	float n1[3]={0.5f, 0.5f, -sqrt(3.0f)/2.0f};
    float n2[3]={0.0f, -1.0f, 0.0f};
    float n3[3]={0.5f, 0.5f, sqrt(3.0f)/2.0f};
    float n4[3]={-1.0f, 0.5f, 0.0f};




float vt[] ={
	 p1[0], p1[1],  p1[2],  //face 1
	 p2[0], p2[1],  p2[2],
	 p3[0], p3[1],  p3[2],
	 	 
	 p3[0], p3[1],  p3[2],  //face 2
	 p2[0], p2[1],  p2[2],
	 p4[0], p4[1],  p4[2],
	 	 
	 p4[0], p4[1],  p4[2],  //face 3
	 p2[0], p2[1],  p2[2],
	 p1[0], p1[1],  p1[2],
	 	 
	 p1[0], p1[1],  p1[2],  //face 4
	 p3[0], p3[1],  p3[2],
	 p4[0], p4[1],  p4[2]};


	 float tt[] ={
	t5[0],t5[1], t2[0],t2[1], t3[0],t3[1], 
	t1[0],t1[1], t5[0],t5[1], t4[0],t4[1],
	t4[0],t4[1], t3[0],t3[1], t5[0],t5[1],
	t5[0],t5[1], t2[0],t2[1], t1[0],t1[1]};


	float nt[] ={
	 n1[0], n1[1],  n1[2],  //face 1
	 n1[0], n1[1],  n1[2],
	 n1[0], n1[1],  n1[2],
	 	 
	 n2[0], n2[1],  n2[2],  //face2
	 n2[0], n2[1],  n2[2],
	 n2[0], n2[1],  n2[2],

	 n3[0], n3[1],  n3[2],  //face 3
	 n3[0], n3[1],  n3[2],
	 n3[0], n3[1],  n3[2],

	 n4[0], n4[1],  n4[2],  //face 4
	 n4[0], n4[1],  n4[2],
	 n4[0], n4[1],  n4[2]};



	memcpy(v,vt,12*3*4);
	memcpy(t,tt,12*2*4);
	memcpy(n,nt,12*3*4);

	return 12;
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

long glzPrimFromIndexArrays(float *v,float *t,float *n, Point3 vert[], Point2 uv[], Point3 norm[], long vert_face[], long uv_face[], long norm_face[],int enteries)
{
	float vt[6000];
	float tt[6000];
	float nt[6000];	


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
				
			vt[(c*3)+0]=(float)vert[vert_face[origin]].x;
			vt[(c*3)+1]=(float)vert[vert_face[origin]].y;
			vt[(c*3)+2]=(float)vert[vert_face[origin]].z;

			tt[(c*2)+0]=(float)uv[uv_face[origin]].x;
			tt[(c*2)+1]=(float)uv[uv_face[origin]].y;

			nt[(c*3)+0]=(float)norm[norm_face[origin]].x;
			nt[(c*3)+1]=(float)norm[norm_face[origin]].y;
			nt[(c*3)+2]=(float)norm[norm_face[origin]].z;

			c++;

			vt[(c*3)+0]=(float)vert[vert_face[i-1]].x;
			vt[(c*3)+1]=(float)vert[vert_face[i-1]].y;
			vt[(c*3)+2]=(float)vert[vert_face[i-1]].z;

			tt[(c*2)+0]=(float)uv[uv_face[i-1]].x;
			tt[(c*2)+1]=(float)uv[uv_face[i-1]].y;

			nt[(c*3)+0]=(float)norm[norm_face[i-1]].x;
			nt[(c*3)+1]=(float)norm[norm_face[i-1]].y;
			nt[(c*3)+2]=(float)norm[norm_face[i-1]].z;

			c++;

			vt[(c*3)+0]=(float)vert[vert_face[i]].x;
			vt[(c*3)+1]=(float)vert[vert_face[i]].y;
			vt[(c*3)+2]=(float)vert[vert_face[i]].z;

			tt[(c*2)+0]=(float)uv[uv_face[i]].x;
			tt[(c*2)+1]=(float)uv[uv_face[i]].y;

			nt[(c*3)+0]=(float)norm[norm_face[i]].x;
			nt[(c*3)+1]=(float)norm[norm_face[i]].y;
			nt[(c*3)+2]=(float)norm[norm_face[i]].z;

			c++;

			}

			i++;		

	}
	
	memcpy(v,vt,c*3*4);
	memcpy(t,tt,c*2*4);
	memcpy(n,nt,c*3*4);

	return c;


}




long glzCountPrimText(char *text)
{
	unsigned int c=0,i=0;


	while(c<strlen(text))
	{

		if((text[c]=='\n') || (text[c]=='\t') ||(text[c]==' '))
		{		
			c++;		
		}
		else
		{		
			i++;
			c++;
		}
		
	}

	return i*6;
}

// glzPrimText is only the first itteration of this, i pan on adding support for more modern font texture generators, currently the function is compattible with "bitmap font builder" since this is
// a leftover from the old NeHe days, eventually i allso plan on adding things like truetype and things like that

long glzPrimText(char *text, float w, float *v, float *t, float *n, glzOrigin origin)
{
	float quv[8];

	float s=1.0f,st=0.33f*s,x=0.0f,y=0.0f;
	float xp=0,yp=-1.0f*s,xs=w,xss=w*0.75f,xssp=w*0.5f;
	unsigned int c=0,iv=0,it=0,i=0;

	while(c<strlen(text))
	{

		if(text[c]=='\n') {yp-=1*s; xp=0; c++;}
		else if(text[c]=='\t')
		{
			if (xp>90*st)	xp=100*st;
			else if (xp>=80*st)	xp=90*st;
			else if (xp>=70*st)	xp=80*st;
			else if (xp>=60*st)	xp=70*st;
			else if (xp>=50*st)	xp=60*st;
			else if (xp>=40*st)	xp=50*st;
			else if (xp>=30*st)	xp=40*st;
			else if (xp>=20*st)	xp=30*st;
			else if (xp>=10*st)	xp=20*st;
			else if (xp>=0)		xp=10*st;
			
			
			c++;
		
		}
		else if(text[c]==' ') { xp+=xssp*s; c++; }
		else 		
		{

		if((text[c]=='i') || (text[c]=='I') || (text[c]=='l') || (text[c]=='1') || (text[c]=='j') || (text[c]=='t') || (text[c]=='!') || (text[c]=='\"') || (text[c]=='\\') || (text[c]=='r'))
		{
			xp-=xs*s;
			xp+=xss*s;
		}
		glzAtlasQuad(16,16,(unsigned int)text[c], origin, quv);
		
	
		// t face 1 (124)
		t[it+0]=quv[0];
		t[it+1]=quv[1];

		t[it+2]=quv[2];
		t[it+3]=quv[3];

		t[it+4]=quv[6];
		t[it+5]=quv[7];

		// t face 2 (234)
		t[it+6]=quv[2];
		t[it+7]=quv[3];

		t[it+8]=quv[4];
		t[it+9]=quv[5];

		t[it+10]=quv[6];
		t[it+11]=quv[7];
		it+=12;

		// v face 1 (124)

		v[iv+0]=0*s+x+xp;
		v[iv+1]=0*s+y+yp;
		v[iv+2]=0;

		v[iv+3]=0*s+x+xp;
		v[iv+4]=1*s+y+yp;
		v[iv+5]=0;

		v[iv+6]=1*s+x+xp;
		v[iv+7]=0*s+y+yp;
		v[iv+8]=0;

		// v face 2 (234)

		v[iv+9]=0*s+x+xp;
		v[iv+10]=1*s+y+yp;
		v[iv+11]=0;

		v[iv+12]=1*s+x+xp;
		v[iv+13]=1*s+y+yp;
		v[iv+14]=0;

		v[iv+15]=1*s+x+xp;
		v[iv+16]=0*s+y+yp;
		v[iv+17]=0;	



		n[iv+0]=0;
		n[iv+1]=1;
		n[iv+2]=0;
			
		n[iv+3]=0;
		n[iv+4]=1;
		n[iv+5]=0;			
		
		n[iv+6]=0;
		n[iv+7]=1;
		n[iv+8]=0;			
		
		n[iv+9]=0;
		n[iv+10]=1;
		n[iv+11]=0;			
		
		n[iv+12]=0;
		n[iv+13]=1;
		n[iv+14]=0;
			
		n[iv+15]=0;
		n[iv+16]=1;
		n[iv+17]=0;

		iv+=18;
			

		if((text[c]=='i') || (text[c]=='I') || (text[c]=='l') || (text[c]=='1') || (text[c]=='j') || (text[c]=='t') || (text[c]=='!') || (text[c]=='\"') || (text[c]=='\\'))
		{
			xp+=xss*s;	
		}
		else 
		{
			xp+=xs*s;
		}


		i++;

		c++;

		}
		


	}


	return i*6;
}


long glzPrimGrid(texture_transform tt, unsigned int x, unsigned int y, glzOrigin origin, float *v, float *t, float *n)
{
	float quv[8];
	unsigned int xi=0,yi=0,it=0,iv=0,c=0,discard=0;


	while (yi<y)
	{
		xi=0;
		while (xi<x)
		{

		discard=0;

		if (tt.type == glzTTType::ATLASARRAY)
			if (tt.atlas[(yi*y)+xi]==9001)			//in case it's totally trasparent then dont make a quad, allso total DBZ reference
				discard=1;

		if (!discard)  
		{

			if (tt.type == glzTTType::ATLASARRAY) {
				glzAtlasQuad(tt.atlas_width, tt.atlas_height, tt.atlas[(yi*y) + xi], origin, quv);
			}
			else { glzAtlasQuad(1, 1, 0, glzOrigin::BOTTOM_RIGHT, quv); }
		
	
		// t face 1 (124)
		t[it+0]=quv[0];
		t[it+1]=quv[1];

		t[it+2]=quv[2];
		t[it+3]=quv[3];

		t[it+4]=quv[6];
		t[it+5]=quv[7];

		// t face 2 (234)
		t[it+6]=quv[2];
		t[it+7]=quv[3];

		t[it+8]=quv[4];
		t[it+9]=quv[5];

		t[it+10]=quv[6];
		t[it+11]=quv[7];
		it+=12;

		// v face 1 (124)

		v[iv+0]=0.0f+xi;
		v[iv+1]=0.0f-yi;
		v[iv+2]=0.0f;

		v[iv+3]=0.0f+xi;
		v[iv+4]=1.0f-yi;
		v[iv+5]=0.0f;

		v[iv+6]=1.0f+xi;
		v[iv+7]=0.0f-yi;
		v[iv+8]=0.0f;

		// v face 2 (234)

		v[iv+9]=0.0f+xi;
		v[iv+10]=1.0f-yi;
		v[iv+11]=0.0f;

		v[iv+12]=1.0f+xi;
		v[iv+13]=1.0f-yi;
		v[iv+14]=0.0f;

		v[iv+15]=1.0f+xi;
		v[iv+16]=0.0f-yi;
		v[iv+17]=0.0f;	



		n[iv+0]=0;
		n[iv+1]=1;
		n[iv+2]=0;
			
		n[iv+3]=0;
		n[iv+4]=1;
		n[iv+5]=0;			
		
		n[iv+6]=0;
		n[iv+7]=1;
		n[iv+8]=0;			
		
		n[iv+9]=0;
		n[iv+10]=1;
		n[iv+11]=0;			
		
		n[iv+12]=0;
		n[iv+13]=1;
		n[iv+14]=0;
			
		n[iv+15]=0;
		n[iv+16]=1;
		n[iv+17]=0;

		iv+=18;

		c++;
		}


		xi++;
	}

		yi++;
	}


	return c*6;
}

// i managed to cut down this from a class into a single function and at the same time made it work better
// the name glzLoafFileGeometryObj is a strong hin that i will add more formats

long glzLoafFileGeometryObj(char filename[255],float *v,float *t,float *n)
{	
	typedef float vec3[3];
	typedef float vec2[2];

	vec3 *vv,*vt,*vn;
	vv = new vec3[60000];
	vt = new vec3[60000];
	vn = new vec3[60000];

	int fv[6000][3];			// polygon references
	int ft[6000][3];
	int fn[6000][3];
	int fs[6000];				// Surface references
	char mat[1000][120];					// material names - 0 terminated

	int f_num=0;
	int v_num=0;
	int vt_num=0;
	int vn_num=0;
	int s_num=0;
	int s_cur=0;

	int f_numt=0;
	int v_numt=0;
	int vt_numt=0;
	int vn_numt=0;
	int s_numt=0;
	int s_curt=0;

	int i=0,ii=0,slash=0;
	int v_a=0,v_b=0,v_c=0,v_d=0,v_e=0;
	int vt_a=0,vt_b=0,vt_c=0,vt_d=0,vt_e=0;
	int vn_a=0,vn_b=0,vn_c=0,vn_d=0,vn_e=0;

	FILE *file;
	char line[120];

	fopen_s( &file, filename,"r");

	if (file == NULL) /* Trying to open file */
		{
			return 0;
		}
	 

	// preparse to find the vertic, texture and normal numbers
	while (!feof(file)) /* Count lines */
	{
		fgets(line,80,file);
		if (!strncmp (line,"v ",2)) v_num++;
		if (!strncmp (line,"vt ",3)) vt_num++;
		if (!strncmp (line,"vn ",3)) vn_num++;
		if (!strncmp (line,"f ",2)) f_num++;
	}
	

	fseek ( file , 0 , SEEK_SET );


	int lt=0;
	while (!feof(file)) /* Count lines */
	{
		fgets(line,80,file);

		if (!strncmp (line,"v ",2)) lt=1;
		if (!strncmp (line,"vt ",3)) lt=2;
		if (!strncmp (line,"vn ",3)) lt=3;
		if (!strncmp (line,"f ",2)) lt=4;
		if (!strncmp (line,"usemtl ",7)) lt=5;
		if (!strncmp (line,"s ",2)) lt=6;
		if (!strncmp (line,"s off",5)) lt=7;

		float x=0.0f,y=0.0f,z=0.0f;
		float u=0.0f,v=0.0f;

		switch(lt)
		{
		case 1:
			
			sscanf_s (line+1,"%f%f%f",&x, &y, &z);
			vv[v_numt][0]=x;
			vv[v_numt][1]=y;
			vv[v_numt][2]=z;
			v_numt++;
			break;
					
		case 2:
			sscanf_s (line+2,"%f%f",&u, &v);
			vt[vt_numt][0]=u;
			vt[vt_numt][1]=v;
			vt_numt++;
			break;
					
		case 3:
			
			sscanf_s (line+2,"%f%f%f",&x, &y, &z);
			vn[vn_numt][0]=x;
			vn[vn_numt][1]=y;
			vn[vn_numt][2]=z;
			vn_numt++;
			break;
					
		case 4:

			i=0;
			ii=0;
			while(i<(int)strlen(line))
				{
					if(line[i] == '/')
						{ii++;}
					i++;
				}
		

			if((ii==8) && (vn_num>0))
			{
				sscanf_s (line+1,"%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d",&v_a, &vt_a, &vn_a, &v_b, &vt_b, &vn_b, &v_c, &vt_c, &vn_c, &v_d, &vt_d, &vn_d);

				fv[f_numt][0]=v_a-1;
				fv[f_numt][1]=v_b-1;
				fv[f_numt][2]=v_c-1;

				ft[f_numt][0]=vt_a-1;
				ft[f_numt][1]=vt_b-1;
				ft[f_numt][2]=vt_c-1;
		
				fn[f_numt][0]=vn_a-1;
				fn[f_numt][1]=vn_b-1;
				fn[f_numt][2]=vn_c-1;
		
				fs[f_numt]=s_cur;
				f_numt++;

		

				fv[f_numt][0]=v_a-1;
				fv[f_numt][1]=v_c-1;
				fv[f_numt][2]=v_d-1;

				ft[f_numt][0]=vt_a-1;
				ft[f_numt][1]=vt_c-1;
				ft[f_numt][2]=vt_d-1;
		
				fn[f_numt][0]=vn_a-1;
				fn[f_numt][1]=vn_c-1;
				fn[f_numt][2]=vn_d-1;
		
				fs[f_numt]=s_cur;
				f_numt++;
			}

	
			if((ii==6) && (vn_num>0))
			{
	
				sscanf_s (line+1,"%d/%d/%d %d/%d/%d %d/%d/%d",&v_a, &vt_a, &vn_a, &v_b, &vt_b, &vn_b, &v_c, &vt_c, &vn_c);
	
				fv[f_numt][0]=v_a-1;
				fv[f_numt][1]=v_b-1;
				fv[f_numt][2]=v_c-1;

				ft[f_numt][0]=vt_a-1;
				ft[f_numt][1]=vt_b-1;
				ft[f_numt][2]=vt_c-1;
		
				fn[f_numt][0]=vn_a-1;
				fn[f_numt][1]=vn_b-1;
				fn[f_numt][2]=vn_c-1;
		
				fs[f_numt]=s_cur;
				f_numt++;

				}
			break;
					
		case 5:
			strcpy_s(mat[s_num],line+7);   // material names could in theory be used to load textures, but in reallity this is probably not ussefull
			mat[s_num][strlen(mat[s_num])-1]=0;
			s_cur=s_num-1;
			s_num++;
			break;
					
		case 6:
			sscanf_s (line,"%d",&s_cur);    // keeps track of surfaces, but otherwise this is useless i only have it here as a reference
			break;
					
		case 7:
			s_cur=0;
			break;
		default:
			break;
		}

	}

	fclose(file);

 i=0;

 while(i<f_numt)
 {

	v[i*3*3+0]=vv[fv[i][0]][0];	
	v[i*3*3+1]=vv[fv[i][0]][1];	
	v[i*3*3+2]=vv[fv[i][0]][2];

	t[i*2*3+0]=vt[ft[i][0]][0];	
	t[i*2*3+1]=vt[ft[i][0]][1];
	
	n[i*3*3+0]=vn[fn[i][0]][0];	
	n[i*3*3+1]=vn[fn[i][0]][1];	
	n[i*3*3+2]=vn[fn[i][0]][2];


	v[i*3*3+3]=vv[fv[i][1]][0];	
	v[i*3*3+4]=vv[fv[i][1]][1];	
	v[i*3*3+5]=vv[fv[i][1]][2];

	t[i*2*3+2]=vt[ft[i][1]][0];	
	t[i*2*3+3]=vt[ft[i][1]][1];
	
	n[i*3*3+3]=vn[fn[i][1]][0];	
	n[i*3*3+4]=vn[fn[i][1]][1];	
	n[i*3*3+5]=vn[fn[i][1]][2];

	
	v[i*3*3+6]=vv[fv[i][2]][0];	
	v[i*3*3+7]=vv[fv[i][2]][1];	
	v[i*3*3+8]=vv[fv[i][2]][2];

	t[i*2*3+4]=vt[ft[i][2]][0];	
	t[i*2*3+5]=vt[ft[i][2]][1];
	
	n[i*3*3+6]=vn[fn[i][2]][0];	
	n[i*3*3+7]=vn[fn[i][2]][1];	
	n[i*3*3+8]=vn[fn[i][2]][2];
	i++;
 }
 
 
 return (f_numt*3);
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


void ini(void)
{

	int i=0;

	while (i<1024)
	{
		active_vao[i]=-1;
		i++;
	}

	glGenBuffers = (PFNGLGENBUFFERSPROC) wglGetProcAddress("glGenBuffers");
	glBindBuffer = (PFNGLBINDBUFFERPROC) wglGetProcAddress("glBindBuffer");
	glBufferData = (PFNGLBUFFERDATAPROC) wglGetProcAddress("glBufferData");
	glDeleteBuffers = (PFNGLDELETEBUFFERSPROC) wglGetProcAddress("glDeleteBuffers");

	glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC) wglGetProcAddress("glBindVertexArray");
	glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC) wglGetProcAddress("glDeleteVertexArrays");
	glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC) wglGetProcAddress("glGenVertexArrays");
	glIsVertexArray = (PFNGLISVERTEXARRAYPROC) wglGetProcAddress("glIsVertexArray");

	glVertexAttribPointer= (PFNGLVERTEXATTRIBPOINTERPROC) wglGetProcAddress("glVertexAttribPointer");
	glBindAttribLocation= (PFNGLBINDATTRIBLOCATIONPROC) wglGetProcAddress("glBindAttribLocation");
	glDisableVertexAttribArray= (PFNGLDISABLEVERTEXATTRIBARRAYPROC) wglGetProcAddress("glDisableVertexAttribArray");
	glEnableVertexAttribArray= (PFNGLENABLEVERTEXATTRIBARRAYPROC) wglGetProcAddress("glEnableVertexAttribArray");

	glGetVertexAttribIuiv= (PFNGLGETVERTEXATTRIBIUIVPROC) wglGetProcAddress("glGetVertexAttribIuiv");
	glIsBuffer= (PFNGLISBUFFERARBPROC) wglGetProcAddress("glIsBuffer");

	isinited=true;
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



long glzVAOMakeFromFile(char filename[255], float matrix[], texture_transform tt, unsigned int *vao)
{
	if(!isinited) ini();

	unsigned int vaopoint;
	vaopoint=*vao;
	if (glIsVertexArray((GLuint)&vao) == GL_FALSE) glzKillVAO(vaopoint, glzVAOType::AUTO);

	float *v,*t,*n;
	v = new float[60000];
	t = new float[60000];
	n = new float[60000];

	long elements=glzLoafFileGeometryObj(filename,v,t,n);

	glzProjectVertexArray(v,matrix,elements);


	if(tt.atlas_width+tt.atlas_height>2)
	{
		glzAtlasUVarrayRemap(tt.firstatlas, elements, tt.atlas_width, tt.atlas_height, glzOrigin::BOTTOM_RIGHT, t);
	}

	glzVAOMakeFromArray(v, t, n, elements, vao, glzVAOType::AUTO);

	delete v;
	delete t;
	delete n;



	return elements;
}



void glzVAOMakeFromArray(float v[], float t[], float n[], long enteties, unsigned int *vao, glzVAOType type)
{
	if(!isinited) ini();
	
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



long glzVAOMakeText(char text[255], float matrix[], float kern, texture_transform tt, unsigned int *vao)
{	
	if(!isinited) ini();

	unsigned int vaopoint;
	vaopoint=*vao;
	if (glIsVertexArray((GLuint)&vao) == GL_FALSE) glzKillVAO(vaopoint, glzVAOType::AUTO);
	float *v,*t,*n;
	
	long verts=glzCountPrimText(text);

	v = new float[verts*3];
	t = new float[verts*2];
	n = new float[verts*3];


	glzPrimText(text, kern, v, t, n, tt.origin);
	glzProjectVertexArray(v,matrix,verts);

	glzVAOMakeFromArray(v, t, n, verts, vao, glzVAOType::AUTO);


	delete[] v;	
	delete[] t;
	delete[] n;
	v=NULL;
	t=NULL;
	n=NULL;

return verts;
	
}

long glzVAOMakeAtlasGrid(unsigned int x, unsigned int y, float matrix[], texture_transform tt, unsigned int *vao)
{
	if(!isinited) ini();

	unsigned char *data;
	data = new unsigned char[1];
	data[0]= 1;

	image_geo_transform igt;  // basically a dummy igt
	igt = glzMakeIGT(glzIGTType::NONE, 0, 0, 0, 0, 0, 0, 0, 0, glzAxis::X, data);
		
	long verts = glzVAOMakeHeightAtlasGrid(x, y, matrix, tt, igt, vao);

	delete data;

	return verts;
}

long glzVAOMakeHeightAtlasGrid(unsigned int x, unsigned int y, float matrix[], texture_transform tt, image_geo_transform igt, unsigned int *vao)
{

	if(!isinited) ini();

	unsigned int vaopoint;
	vaopoint=*vao;
	if (glIsVertexArray((GLuint)&vao) == GL_FALSE) glzKillVAO(vaopoint, glzVAOType::AUTO);
	float *v,*t,*n;
	
	long verts=(x*y*6);

	v = new float[verts*3];
	t = new float[verts*2];
	n = new float[verts*3];

	glzPrimGrid(tt, x, y, tt.origin, v, t, n);

	if (igt.type == glzIGTType::DISPLACE_ADD) glzIGT(v, igt, verts);

	if (tt.type == glzTTType::VERTEX_COORD_ADOPT) glzVert2TexcoordRescale(v, t, tt, verts);

	glzProjectVertexArray(v,matrix,verts);

	glzVAOMakeFromArray(v, t, n, verts, vao, glzVAOType::AUTO);


	delete[] v;	
	delete[] t;
	delete[] n;
	v=NULL;
	t=NULL;
	n=NULL;

return verts;
}


long glzVAOCountPrimitiveVerts(primitive_gen pg)
{

switch (pg.type)
	{	
	
	case glzPrimitive::CUBE:
	case glzPrimitive::HEXAHEDRON:
		return 36;		
		break;

	case glzPrimitive::TETRAHEDRON:
		return 12;
		break;

	case glzPrimitive::PYRAMID:
		return glzCountFromIndexArrays(pyramid_face,sizeof(pyramid_face)/sizeof(long));
		break;

	case glzPrimitive::OCTAHEDRON:
		return glzCountFromIndexArrays(octahedron_face,sizeof(octahedron_face)/sizeof(long));
		break;

	case glzPrimitive::DODECAHEDRON:
		return glzCountFromIndexArrays(dodecahedron_face,sizeof(dodecahedron_face)/sizeof(long));
		break;

	case glzPrimitive::ICOSAHEDRON:
		return glzCountFromIndexArrays(icosahedron_face,sizeof(icosahedron_face)/sizeof(long));
		break;

	case glzPrimitive::ICOSIDODECAHEDRON:
		return glzCountFromIndexArrays(icosidodecahederon_face,sizeof(icosidodecahederon_face)/sizeof(long));
		break;

	case glzPrimitive::FSQ:
		return 6;		
		break;
	case glzPrimitive::RANDOM_POINT:
		return (long)pg.resolution_x;
		break;
	case glzPrimitive::SPRITE_ATLAS_ARRAY:
		return pg.tt.atlas_width*pg.tt.atlas_height*6;	
		break;		
		
	default:
		return 0;
		break;

	}
}

long glzVAOMakePrimitive(primitive_gen pg, unsigned int *vao)
{
	if(!isinited) ini();

	unsigned int vaopoint;
	vaopoint=*vao;
	if (glIsVertexArray((GLuint)&vao) == GL_FALSE) glzKillVAO(vaopoint, glzVAOType::AUTO);

	primitive_gen pg2[2];
	pg2[0]=pg;	
	
	long verts=glzVAOMakePrimitives(1,pg2,vao);
	return verts;

}

long glzVAOMakePrimitives(int num, primitive_gen pg[], unsigned int *vao)
{
	if(!isinited) ini();



	unsigned int vaopoint;
	vaopoint=*vao;
	if (glIsVertexArray((GLuint)&vao) == GL_FALSE) glzKillVAO(vaopoint, glzVAOType::AUTO);

	int i=0;
	long verts=0;

	while(i<num)
	{
		verts+=glzVAOCountPrimitiveVerts(pg[i]);
		i++;
	}

	

	float *v,*t,*n;
	v = new float[verts*3];
	t = new float[verts*2];
	n = new float[verts*3];




	int curvert=0;
	int oldcurvert=0;
	int saic=0,sai=0;
	i=0;
	while(i<num)
	{

		switch (pg[i].type)
		{	
	
		case glzPrimitive::CUBE:
		case glzPrimitive::HEXAHEDRON:
			curvert=glzPrimCubeverts(v+oldcurvert*3,t+oldcurvert*2,n+oldcurvert*3);	

			//curvert=glzPrimFromIndexArrays(v+oldcurvert*3,t+oldcurvert*2,n+oldcurvert*3,cube_vertex,cube_uv,cube_normal,cube_face,cube_uvface,cube_nface,sizeof(cube_face)/sizeof(long));
			glzProjectVertexArray(v+oldcurvert*3,pg[i].matrix,curvert);


			if((pg[i].tt.atlas_height>1)|| (pg[i].tt.atlas_width>1))
		    {
				int aw=pg[i].tt.atlas_width;
				
				if (pg[i].tt.type == glzTTType::ATLAS_CUBE_TBS)
				{
					glzAtlasUVarrayRemap(pg[i].tt.firstatlas, 6, pg[i].tt.atlas_width, pg[i].tt.atlas_height, pg[i].tt.origin, t + oldcurvert * 2);
					glzAtlasUVarrayRemap(pg[i].tt.firstatlas + 1, 6, pg[i].tt.atlas_width, pg[i].tt.atlas_height, pg[i].tt.origin, t + (oldcurvert + 6) * 2);
					glzAtlasUVarrayRemap(pg[i].tt.firstatlas + 2, curvert - 12, pg[i].tt.atlas_width, pg[i].tt.atlas_height, pg[i].tt.origin, t + (oldcurvert + 12) * 2);
				}

				else if (pg[i].tt.type == glzTTType::ATLAS_CUBE_INDFACE)
				{
					glzAtlasUVarrayRemap(pg[i].tt.firstatlas + 0, 6, pg[i].tt.atlas_width, pg[i].tt.atlas_height, pg[i].tt.origin, t + (oldcurvert)* 2);
					glzAtlasUVarrayRemap(pg[i].tt.firstatlas + 1, 6, pg[i].tt.atlas_width, pg[i].tt.atlas_height, pg[i].tt.origin, t + (6 + oldcurvert) * 2);

					glzAtlasUVarrayRemap(pg[i].tt.firstatlas + 2, 6, pg[i].tt.atlas_width, pg[i].tt.atlas_height, pg[i].tt.origin, t + (12 + oldcurvert) * 2);
					glzAtlasUVarrayRemap(pg[i].tt.firstatlas + 3, 6, pg[i].tt.atlas_width, pg[i].tt.atlas_height, pg[i].tt.origin, t + (18 + oldcurvert) * 2);

					glzAtlasUVarrayRemap(pg[i].tt.firstatlas + 4, 6, pg[i].tt.atlas_width, pg[i].tt.atlas_height, pg[i].tt.origin, t + (24 + oldcurvert) * 2);
					glzAtlasUVarrayRemap(pg[i].tt.firstatlas + 5, 6, pg[i].tt.atlas_width, pg[i].tt.atlas_height, pg[i].tt.origin, t + (30 + oldcurvert) * 2);
				}

				else if (pg[i].tt.type == glzTTType::ATLAS_CUBE_CROSS)
				{					
					glzAtlasUVarrayRemapRotate(3, pg[i].tt.firstatlas + 1, 6, pg[i].tt.atlas_width, pg[i].tt.atlas_height, pg[i].tt.origin, t + (oldcurvert)* 2);
					glzAtlasUVarrayRemapRotate(3, pg[i].tt.firstatlas + aw + aw + 1, 6, pg[i].tt.atlas_width, pg[i].tt.atlas_height, pg[i].tt.origin, t + (6 + oldcurvert) * 2);

					glzAtlasUVarrayRemap(pg[i].tt.firstatlas + aw, 6, pg[i].tt.atlas_width, pg[i].tt.atlas_height, pg[i].tt.origin, t + (12 + oldcurvert) * 2);
					glzAtlasUVarrayRemap(pg[i].tt.firstatlas + aw + 1, 6, pg[i].tt.atlas_width, pg[i].tt.atlas_height, pg[i].tt.origin, t + (18 + oldcurvert) * 2);

					glzAtlasUVarrayRemap(pg[i].tt.firstatlas + aw + 2, 6, pg[i].tt.atlas_width, pg[i].tt.atlas_height, pg[i].tt.origin, t + (24 + oldcurvert) * 2);
					glzAtlasUVarrayRemapRotate(2, pg[i].tt.firstatlas + aw + aw + aw + 1, 6, pg[i].tt.atlas_width, pg[i].tt.atlas_height, pg[i].tt.origin, t + (30 + oldcurvert) * 2);
				}

				else { glzAtlasUVarrayRemap(pg[i].tt.firstatlas, curvert, pg[i].tt.atlas_width, pg[i].tt.atlas_height, pg[i].tt.origin, t + oldcurvert * 2); }

			}



			break;



		case glzPrimitive::TETRAHEDRON:
			curvert=glzPrimTetra(v+oldcurvert*3,t+oldcurvert*2,n+oldcurvert*3);	
			glzProjectVertexArray(v+oldcurvert*3,pg[i].matrix,curvert);
			break;	

		
		case glzPrimitive::PYRAMID:
			curvert=glzPrimFromIndexArrays(v+oldcurvert*3,t+oldcurvert*2,n+oldcurvert*3,pyramid_vertex,pyramid_uv,pyramid_normal,pyramid_face,pyramid_uvface,pyramid_nface,sizeof(pyramid_face)/sizeof(long));
			glzProjectVertexArray(v+oldcurvert*3,pg[i].matrix,curvert);
			break;

		case glzPrimitive::OCTAHEDRON:
			curvert=glzPrimFromIndexArrays(v+oldcurvert*3,t+oldcurvert*2,n+oldcurvert*3,octahedron_vertex,octahedron_uv,octahedron_normal,octahedron_face,octahedron_uvface,octahedron_nface,sizeof(octahedron_face)/sizeof(long));
			glzProjectVertexArray(v+oldcurvert*3,pg[i].matrix,curvert);
			break;

		case glzPrimitive::DODECAHEDRON:
			curvert=glzPrimFromIndexArrays(v+oldcurvert*3,t+oldcurvert*2,n+oldcurvert*3,dodecahedron_vertex,dodecahedron_uv,dodecahedron_normal,dodecahedron_face,dodecahedron_uvface,dodecahedron_nface,sizeof(dodecahedron_face)/sizeof(long));
			glzProjectVertexArray(v+oldcurvert*3,pg[i].matrix,curvert);
			break;

		case glzPrimitive::ICOSAHEDRON:
			curvert=glzPrimFromIndexArrays(v+oldcurvert*3,t+oldcurvert*2,n+oldcurvert*3,icosahedron_vertex,icosahedron_uv,icosahedron_normal,icosahedron_face,icosahedron_uvface,icosahedron_nface,sizeof(icosahedron_face)/sizeof(long));
			glzProjectVertexArray(v+oldcurvert*3,pg[i].matrix,curvert);
			break;

		case glzPrimitive::ICOSIDODECAHEDRON:
			curvert=glzPrimFromIndexArrays(v+oldcurvert*3,t+oldcurvert*2,n+oldcurvert*3,icosidodecahederon_vertex,icosidodecahederon_uv,icosidodecahederon_normal,icosidodecahederon_face,icosidodecahederon_uvface,icosidodecahederon_nface,sizeof(icosidodecahederon_face)/sizeof(long));
			glzProjectVertexArray(v+oldcurvert*3,pg[i].matrix,curvert);
			break;

			

		case glzPrimitive::FSQ:
			curvert=glzPrimFSQ(v+oldcurvert*3,t+oldcurvert*2,n+oldcurvert*3);
			break;

		case glzPrimitive::RANDOM_POINT:
			curvert+=glzPrimRandom(v+oldcurvert,t+oldcurvert,n+oldcurvert,pg[i].resolution_x);	
			glzProjectVertexArray(v+oldcurvert*3,pg[i].matrix,curvert);
			break;

		case glzPrimitive::SPRITE_ATLAS_ARRAY:
				
				saic=pg[i].tt.atlas_width*pg[i].tt.atlas_height;	
								
				sai=0;
				

				while (sai<saic)
				{
					curvert=glzPrimFSQ(v+oldcurvert*3,t+oldcurvert*2,n+oldcurvert*3);
					
					glzAtlasUVarrayRemap(sai, 6, pg[i].tt.atlas_width, pg[i].tt.atlas_height, pg[i].tt.origin, t + oldcurvert * 2);
					oldcurvert+=curvert;

					sai++;
				}

				oldcurvert-=curvert;
			break;
		
		default:
			break;

		}

		if ((pg[i].tt.atlas_width + pg[i].tt.atlas_height>2) && (pg[i].type != glzPrimitive::CUBE) && (pg[i].type != glzPrimitive::HEXAHEDRON) && (pg[i].type != glzPrimitive::SPRITE_ATLAS_ARRAY))
		{
			glzAtlasUVarrayRemap(pg[i].tt.firstatlas, curvert, pg[i].tt.atlas_width, pg[i].tt.atlas_height, pg[i].tt.origin, t + oldcurvert * 2);
		}

		oldcurvert+=curvert;
		i++;
	}



	glzVAOMakeFromArray(v, t, n, verts, vao, glzVAOType::AUTO);


	delete[] v;	
	delete[] t;
	delete[] n;
	v=NULL;
	t=NULL;
	n=NULL;

return verts;
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
			X + W, Y , Z,
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


void glzDirectPointArrayRender(float v[], float t[], int E)
{

	unsigned int localVAO;


	float n[] = {0.0f, 0.0f, 1.0f};
		glzVAOMakeFromArray(v, t, n, E, &localVAO, glzVAOType::VERTEX_TEXTURE);


	glzDrawVAO(0, E, localVAO, GL_POINTS);
	glzKillVAO(localVAO, glzVAOType::VERTEX_TEXTURE);

	return;
}





void glzKillVAO(unsigned int vao, glzVAOType type)
{
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
	if(!isinited) ini();

	glBindVertexArray(vao);
	glDrawArrays(type, 0, enteties);
	glBindVertexArray(0);
	return;
}


void glzDrawVAO(long offset, long enteties, unsigned int vao, unsigned int type)
{
	if(!isinited) ini();

	glBindVertexArray(vao);
	glDrawArrays(type, offset, enteties);
	glBindVertexArray(0);
	return;
}


// there are a lot of things i like to add here and if it becomes to mcuh i might split it up into 3 files
// one for generated geometry, loaded geometry and other stuff.
// if you have some fun geometry generation to add then look at glzVAOMakeHeightAtlasGrid since it will be more or less how all of them will look like once i expand
// the image geo transform to work on everything
