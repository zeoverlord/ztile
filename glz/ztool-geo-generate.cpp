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
#include "ztool-geo.h"
#include "ztool-glz.h"
#include <stdio.h>
#include <windows.h>													// Header File For The Windows Library
#include <gl/gl.h>														// Header File For The OpenGL32 Library
#include <gl/glu.h>														// Header File For The GLu32 Library
#include <gl/glext.h>
#include "ztool-geo-generate.h"

#include "primitives.h"
using namespace std;

static PFNGLISVERTEXARRAYPROC					glIsVertexArray;


static bool isinited_geo_generate;

void ini_geo_generate(void)
{

	glIsVertexArray = (PFNGLISVERTEXARRAYPROC)wglGetProcAddress("glIsVertexArray");

	isinited_geo_generate = true;
}





long glzPrimFSQ(float *v, float *t, float *n)
{
	float vt[] = {
		-1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,
		1.0f, 1.0f, 1.0f };

	float tt[] = {
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 1.0f };

	// + or - 0.0025f is to adjust the texture coords for full screen viewingso to reduce edge bleeding, though it might have to be adjusted for later, this is for 800x600, i think

	float nt[] = {
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f };


	memcpy(v, vt, 6 * 3 * 4);
	memcpy(t, tt, 6 * 2 * 4);
	memcpy(n, nt, 6 * 3 * 4);


	return 6;
}

long glzPrimRandom(float *v, float *t, float *n, int num)
{
	int i = 0;
	float nt[3];

	for (i = 0; i<num * 3; i++)
	{
		v[i] = glzRandfs()*0.5f;
	}

	for (i = 0; i<num * 2; i++)
	{
		t[i] = glzRandf();
	}

	for (i = 0; i<num * 3; i += 3)
	{
		nt[0] = glzRandfs();
		nt[1] = glzRandfs();
		nt[2] = glzRandfs();
		glzNormalizef(&nt[0], 1.0f);
		n[i + 0] = nt[0];
		n[i + 1] = nt[1];
		n[i + 2] = nt[2];
	}

	return (long)num;
}

long glzPrimTetra(float *v, float *t, float *n)
{


	float p1[3] = { 0, -0.5f, (sqrt(3.0f) - (1 / sqrt(3.0f)))*0.5f };
	float p2[3] = { 0.5, -0.5f, -0.5f / sqrt(3.0f) };
	float p3[3] = { -0.5, -0.5f, -0.5f / sqrt(3.0f) };
	float p4[3] = { 0, 1 * sqrt(2.0f / 3.0f) - 0.5f, 0 };

	float t1[2] = { 0, 0 };
	float t2[2] = { 0, 1 };
	float t3[2] = { 1, 1 };
	float t4[2] = { 1, 0 };
	float t5[2] = { 0.5, 0.5 };

	float n1[3] = { 0.5f, 0.5f, -sqrt(3.0f) / 2.0f };
	float n2[3] = { 0.0f, -1.0f, 0.0f };
	float n3[3] = { 0.5f, 0.5f, sqrt(3.0f) / 2.0f };
	float n4[3] = { -1.0f, 0.5f, 0.0f };




	float vt[] = {
		p1[0], p1[1], p1[2],  //face 1
		p2[0], p2[1], p2[2],
		p3[0], p3[1], p3[2],

		p3[0], p3[1], p3[2],  //face 2
		p2[0], p2[1], p2[2],
		p4[0], p4[1], p4[2],

		p4[0], p4[1], p4[2],  //face 3
		p2[0], p2[1], p2[2],
		p1[0], p1[1], p1[2],

		p1[0], p1[1], p1[2],  //face 4
		p3[0], p3[1], p3[2],
		p4[0], p4[1], p4[2] };


	float tt[] = {
		t5[0], t5[1], t2[0], t2[1], t3[0], t3[1],
		t1[0], t1[1], t5[0], t5[1], t4[0], t4[1],
		t4[0], t4[1], t3[0], t3[1], t5[0], t5[1],
		t5[0], t5[1], t2[0], t2[1], t1[0], t1[1] };


	float nt[] = {
		n1[0], n1[1], n1[2],  //face 1
		n1[0], n1[1], n1[2],
		n1[0], n1[1], n1[2],

		n2[0], n2[1], n2[2],  //face2
		n2[0], n2[1], n2[2],
		n2[0], n2[1], n2[2],

		n3[0], n3[1], n3[2],  //face 3
		n3[0], n3[1], n3[2],
		n3[0], n3[1], n3[2],

		n4[0], n4[1], n4[2],  //face 4
		n4[0], n4[1], n4[2],
		n4[0], n4[1], n4[2] };



	memcpy(v, vt, 12 * 3 * 4);
	memcpy(t, tt, 12 * 2 * 4);
	memcpy(n, nt, 12 * 3 * 4);

	return 12;
}



long glzPrimFromIndexArrays(float *v, float *t, float *n, Point3 vert[], Point2 uv[], Point3 norm[], long vert_face[], long uv_face[], long norm_face[], int enteries)
{
	float vt[6000];
	float tt[6000];
	float nt[6000];


	int faces = enteries;

	int i = 2, origin = 0, c = 0;

	while (i<faces)
	{

		if (vert_face[i] == -1)
		{
			origin = i + 1;
			i = origin + 2;

		}

		if (origin<faces)
		{

			vt[(c * 3) + 0] = (float)vert[vert_face[origin]].x;
			vt[(c * 3) + 1] = (float)vert[vert_face[origin]].y;
			vt[(c * 3) + 2] = (float)vert[vert_face[origin]].z;

			tt[(c * 2) + 0] = (float)uv[uv_face[origin]].x;
			tt[(c * 2) + 1] = (float)uv[uv_face[origin]].y;

			nt[(c * 3) + 0] = (float)norm[norm_face[origin]].x;
			nt[(c * 3) + 1] = (float)norm[norm_face[origin]].y;
			nt[(c * 3) + 2] = (float)norm[norm_face[origin]].z;

			c++;

			vt[(c * 3) + 0] = (float)vert[vert_face[i - 1]].x;
			vt[(c * 3) + 1] = (float)vert[vert_face[i - 1]].y;
			vt[(c * 3) + 2] = (float)vert[vert_face[i - 1]].z;

			tt[(c * 2) + 0] = (float)uv[uv_face[i - 1]].x;
			tt[(c * 2) + 1] = (float)uv[uv_face[i - 1]].y;

			nt[(c * 3) + 0] = (float)norm[norm_face[i - 1]].x;
			nt[(c * 3) + 1] = (float)norm[norm_face[i - 1]].y;
			nt[(c * 3) + 2] = (float)norm[norm_face[i - 1]].z;

			c++;

			vt[(c * 3) + 0] = (float)vert[vert_face[i]].x;
			vt[(c * 3) + 1] = (float)vert[vert_face[i]].y;
			vt[(c * 3) + 2] = (float)vert[vert_face[i]].z;

			tt[(c * 2) + 0] = (float)uv[uv_face[i]].x;
			tt[(c * 2) + 1] = (float)uv[uv_face[i]].y;

			nt[(c * 3) + 0] = (float)norm[norm_face[i]].x;
			nt[(c * 3) + 1] = (float)norm[norm_face[i]].y;
			nt[(c * 3) + 2] = (float)norm[norm_face[i]].z;

			c++;

		}

		i++;

	}

	memcpy(v, vt, c * 3 * 4);
	memcpy(t, tt, c * 2 * 4);
	memcpy(n, nt, c * 3 * 4);

	return c;


}





long glzPrimGrid(texture_transform tt, unsigned int x, unsigned int y, glzOrigin origin, float *v, float *t, float *n)
{
	float quv[8];
	unsigned int xi = 0, yi = 0, it = 0, iv = 0, c = 0, discard = 0;


	while (yi<y)
	{
		xi = 0;
		while (xi<x)
		{

			discard = 0;

			if (tt.type == glzTTType::ATLASARRAY)
			if (tt.atlas[(yi*y) + xi] == 9001)			//in case it's totally trasparent then dont make a quad, allso total DBZ reference
				discard = 1;

			if (!discard)
			{

				if (tt.type == glzTTType::ATLASARRAY) {
					glzAtlasQuad(tt.atlas_width, tt.atlas_height, tt.atlas[(yi*y) + xi], origin, quv);
				}
				else { glzAtlasQuad(1, 1, 0, glzOrigin::BOTTOM_RIGHT, quv); }


				// t face 1 (124)
				t[it + 0] = quv[0];
				t[it + 1] = quv[1];

				t[it + 2] = quv[2];
				t[it + 3] = quv[3];

				t[it + 4] = quv[6];
				t[it + 5] = quv[7];

				// t face 2 (234)
				t[it + 6] = quv[2];
				t[it + 7] = quv[3];

				t[it + 8] = quv[4];
				t[it + 9] = quv[5];

				t[it + 10] = quv[6];
				t[it + 11] = quv[7];
				it += 12;

				// v face 1 (124)

				v[iv + 0] = 0.0f + xi;
				v[iv + 1] = 0.0f - yi;
				v[iv + 2] = 0.0f;

				v[iv + 3] = 0.0f + xi;
				v[iv + 4] = 1.0f - yi;
				v[iv + 5] = 0.0f;

				v[iv + 6] = 1.0f + xi;
				v[iv + 7] = 0.0f - yi;
				v[iv + 8] = 0.0f;

				// v face 2 (234)

				v[iv + 9] = 0.0f + xi;
				v[iv + 10] = 1.0f - yi;
				v[iv + 11] = 0.0f;

				v[iv + 12] = 1.0f + xi;
				v[iv + 13] = 1.0f - yi;
				v[iv + 14] = 0.0f;

				v[iv + 15] = 1.0f + xi;
				v[iv + 16] = 0.0f - yi;
				v[iv + 17] = 0.0f;



				n[iv + 0] = 0;
				n[iv + 1] = 1;
				n[iv + 2] = 0;

				n[iv + 3] = 0;
				n[iv + 4] = 1;
				n[iv + 5] = 0;

				n[iv + 6] = 0;
				n[iv + 7] = 1;
				n[iv + 8] = 0;

				n[iv + 9] = 0;
				n[iv + 10] = 1;
				n[iv + 11] = 0;

				n[iv + 12] = 0;
				n[iv + 13] = 1;
				n[iv + 14] = 0;

				n[iv + 15] = 0;
				n[iv + 16] = 1;
				n[iv + 17] = 0;

				iv += 18;

				c++;
			}


			xi++;
		}

		yi++;
	}


	return c * 6;
}

// i managed to cut down this from a class into a single function and at the same time made it work better
// the name glzLoafFileGeometryObj is a strong hin that i will add more formats

long glzLoafFileGeometryObj(char filename[255], float *v, float *t, float *n)
{
	typedef float vec3[3];
	typedef float vec2[2];

	vec3 *vv, *vt, *vn;
	vv = new vec3[60000];
	vt = new vec3[60000];
	vn = new vec3[60000];

	int fv[6000][3];			// polygon references
	int ft[6000][3];
	int fn[6000][3];
	int fs[6000];				// Surface references
	char mat[1000][120];					// material names - 0 terminated

	int f_num = 0;
	int v_num = 0;
	int vt_num = 0;
	int vn_num = 0;
	int s_num = 0;
	int s_cur = 0;

	int f_numt = 0;
	int v_numt = 0;
	int vt_numt = 0;
	int vn_numt = 0;
	int s_numt = 0;
	int s_curt = 0;

	int i = 0, ii = 0, slash = 0;
	int v_a = 0, v_b = 0, v_c = 0, v_d = 0, v_e = 0;
	int vt_a = 0, vt_b = 0, vt_c = 0, vt_d = 0, vt_e = 0;
	int vn_a = 0, vn_b = 0, vn_c = 0, vn_d = 0, vn_e = 0;

	FILE *file;
	char line[120];

	fopen_s(&file, filename, "r");

	if (file == NULL) /* Trying to open file */
	{
		return 0;
	}


	// preparse to find the vertic, texture and normal numbers
	while (!feof(file)) /* Count lines */
	{
		fgets(line, 80, file);
		if (!strncmp(line, "v ", 2)) v_num++;
		if (!strncmp(line, "vt ", 3)) vt_num++;
		if (!strncmp(line, "vn ", 3)) vn_num++;
		if (!strncmp(line, "f ", 2)) f_num++;
	}


	fseek(file, 0, SEEK_SET);


	int lt = 0;
	while (!feof(file)) /* Count lines */
	{
		fgets(line, 80, file);

		if (!strncmp(line, "v ", 2)) lt = 1;
		if (!strncmp(line, "vt ", 3)) lt = 2;
		if (!strncmp(line, "vn ", 3)) lt = 3;
		if (!strncmp(line, "f ", 2)) lt = 4;
		if (!strncmp(line, "usemtl ", 7)) lt = 5;
		if (!strncmp(line, "s ", 2)) lt = 6;
		if (!strncmp(line, "s off", 5)) lt = 7;

		float x = 0.0f, y = 0.0f, z = 0.0f;
		float u = 0.0f, v = 0.0f;

		switch (lt)
		{
		case 1:

			sscanf_s(line + 1, "%f%f%f", &x, &y, &z);
			vv[v_numt][0] = x;
			vv[v_numt][1] = y;
			vv[v_numt][2] = z;
			v_numt++;
			break;

		case 2:
			sscanf_s(line + 2, "%f%f", &u, &v);
			vt[vt_numt][0] = u;
			vt[vt_numt][1] = v;
			vt_numt++;
			break;

		case 3:

			sscanf_s(line + 2, "%f%f%f", &x, &y, &z);
			vn[vn_numt][0] = x;
			vn[vn_numt][1] = y;
			vn[vn_numt][2] = z;
			vn_numt++;
			break;

		case 4:

			i = 0;
			ii = 0;
			while (i<(int)strlen(line))
			{
				if (line[i] == '/')
				{
					ii++;
				}
				i++;
			}


			if ((ii == 8) && (vn_num>0))
			{
				sscanf_s(line + 1, "%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d", &v_a, &vt_a, &vn_a, &v_b, &vt_b, &vn_b, &v_c, &vt_c, &vn_c, &v_d, &vt_d, &vn_d);

				fv[f_numt][0] = v_a - 1;
				fv[f_numt][1] = v_b - 1;
				fv[f_numt][2] = v_c - 1;

				ft[f_numt][0] = vt_a - 1;
				ft[f_numt][1] = vt_b - 1;
				ft[f_numt][2] = vt_c - 1;

				fn[f_numt][0] = vn_a - 1;
				fn[f_numt][1] = vn_b - 1;
				fn[f_numt][2] = vn_c - 1;

				fs[f_numt] = s_cur;
				f_numt++;



				fv[f_numt][0] = v_a - 1;
				fv[f_numt][1] = v_c - 1;
				fv[f_numt][2] = v_d - 1;

				ft[f_numt][0] = vt_a - 1;
				ft[f_numt][1] = vt_c - 1;
				ft[f_numt][2] = vt_d - 1;

				fn[f_numt][0] = vn_a - 1;
				fn[f_numt][1] = vn_c - 1;
				fn[f_numt][2] = vn_d - 1;

				fs[f_numt] = s_cur;
				f_numt++;
			}


			if ((ii == 6) && (vn_num>0))
			{

				sscanf_s(line + 1, "%d/%d/%d %d/%d/%d %d/%d/%d", &v_a, &vt_a, &vn_a, &v_b, &vt_b, &vn_b, &v_c, &vt_c, &vn_c);

				fv[f_numt][0] = v_a - 1;
				fv[f_numt][1] = v_b - 1;
				fv[f_numt][2] = v_c - 1;

				ft[f_numt][0] = vt_a - 1;
				ft[f_numt][1] = vt_b - 1;
				ft[f_numt][2] = vt_c - 1;

				fn[f_numt][0] = vn_a - 1;
				fn[f_numt][1] = vn_b - 1;
				fn[f_numt][2] = vn_c - 1;

				fs[f_numt] = s_cur;
				f_numt++;

			}
			break;

		case 5:
			strcpy_s(mat[s_num], line + 7);   // material names could in theory be used to load textures, but in reallity this is probably not ussefull
			mat[s_num][strlen(mat[s_num]) - 1] = 0;
			s_cur = s_num - 1;
			s_num++;
			break;

		case 6:
			sscanf_s(line, "%d", &s_cur);    // keeps track of surfaces, but otherwise this is useless i only have it here as a reference
			break;

		case 7:
			s_cur = 0;
			break;
		default:
			break;
		}

	}

	fclose(file);

	i = 0;

	while (i<f_numt)
	{

		v[i * 3 * 3 + 0] = vv[fv[i][0]][0];
		v[i * 3 * 3 + 1] = vv[fv[i][0]][1];
		v[i * 3 * 3 + 2] = vv[fv[i][0]][2];

		t[i * 2 * 3 + 0] = vt[ft[i][0]][0];
		t[i * 2 * 3 + 1] = vt[ft[i][0]][1];

		n[i * 3 * 3 + 0] = vn[fn[i][0]][0];
		n[i * 3 * 3 + 1] = vn[fn[i][0]][1];
		n[i * 3 * 3 + 2] = vn[fn[i][0]][2];


		v[i * 3 * 3 + 3] = vv[fv[i][1]][0];
		v[i * 3 * 3 + 4] = vv[fv[i][1]][1];
		v[i * 3 * 3 + 5] = vv[fv[i][1]][2];

		t[i * 2 * 3 + 2] = vt[ft[i][1]][0];
		t[i * 2 * 3 + 3] = vt[ft[i][1]][1];

		n[i * 3 * 3 + 3] = vn[fn[i][1]][0];
		n[i * 3 * 3 + 4] = vn[fn[i][1]][1];
		n[i * 3 * 3 + 5] = vn[fn[i][1]][2];


		v[i * 3 * 3 + 6] = vv[fv[i][2]][0];
		v[i * 3 * 3 + 7] = vv[fv[i][2]][1];
		v[i * 3 * 3 + 8] = vv[fv[i][2]][2];

		t[i * 2 * 3 + 4] = vt[ft[i][2]][0];
		t[i * 2 * 3 + 5] = vt[ft[i][2]][1];

		n[i * 3 * 3 + 6] = vn[fn[i][2]][0];
		n[i * 3 * 3 + 7] = vn[fn[i][2]][1];
		n[i * 3 * 3 + 8] = vn[fn[i][2]][2];
		i++;
	}


	return (f_numt * 3);
}


long glzVAOMakeFromFile(char filename[255], float matrix[], texture_transform tt, unsigned int *vao)
{
	if (!isinited_geo_generate) ini_geo_generate();

	unsigned int vaopoint;
	vaopoint = *vao;
	if (glIsVertexArray((GLuint)&vao) == GL_FALSE) glzKillVAO(vaopoint, glzVAOType::AUTO);

	float *v, *t, *n;
	v = new float[60000];
	t = new float[60000];
	n = new float[60000];

	long elements = glzLoafFileGeometryObj(filename, v, t, n);

	glzProjectVertexArray(v, matrix, elements);


	if (tt.atlas_width + tt.atlas_height>2)
	{
		glzAtlasUVarrayRemap(tt.firstatlas, elements, tt.atlas_width, tt.atlas_height, glzOrigin::BOTTOM_RIGHT, t);
	}

	glzVAOMakeFromArray(v, t, n, elements, vao, glzVAOType::AUTO);

	delete v;
	delete t;
	delete n;



	return elements;
}





long glzVAOMakeAtlasGrid(unsigned int x, unsigned int y, float matrix[], texture_transform tt, unsigned int *vao)
{
	if (!isinited_geo_generate) ini_geo_generate();

	unsigned char *data;
	data = new unsigned char[1];
	data[0] = 1;

	image_geo_transform igt;  // basically a dummy igt
	igt = glzMakeIGT(glzIGTType::NONE, 0, 0, 0, 0, 0, 0, 0, 0, glzAxis::X, data);

	long verts = glzVAOMakeHeightAtlasGrid(x, y, matrix, tt, igt, vao);

	delete data;

	return verts;
}

long glzVAOMakeHeightAtlasGrid(unsigned int x, unsigned int y, float matrix[], texture_transform tt, image_geo_transform igt, unsigned int *vao)
{

	if (!isinited_geo_generate) ini_geo_generate();

	unsigned int vaopoint;
	vaopoint = *vao;
	if (glIsVertexArray((GLuint)&vao) == GL_FALSE) glzKillVAO(vaopoint, glzVAOType::AUTO);
	float *v, *t, *n;

	long verts = (x*y * 6);

	v = new float[verts * 3];
	t = new float[verts * 2];
	n = new float[verts * 3];

	glzPrimGrid(tt, x, y, tt.origin, v, t, n);

	if (igt.type == glzIGTType::DISPLACE_ADD) glzIGT(v, igt, verts);

	if (tt.type == glzTTType::VERTEX_COORD_ADOPT) glzVert2TexcoordRescale(v, t, tt, verts);

	glzProjectVertexArray(v, matrix, verts);

	glzVAOMakeFromArray(v, t, n, verts, vao, glzVAOType::AUTO);


	delete[] v;
	delete[] t;
	delete[] n;
	v = NULL;
	t = NULL;
	n = NULL;

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
		return glzCountFromIndexArrays(pyramid_face, sizeof(pyramid_face) / sizeof(long));
		break;

	case glzPrimitive::OCTAHEDRON:
		return glzCountFromIndexArrays(octahedron_face, sizeof(octahedron_face) / sizeof(long));
		break;

	case glzPrimitive::DODECAHEDRON:
		return glzCountFromIndexArrays(dodecahedron_face, sizeof(dodecahedron_face) / sizeof(long));
		break;

	case glzPrimitive::ICOSAHEDRON:
		return glzCountFromIndexArrays(icosahedron_face, sizeof(icosahedron_face) / sizeof(long));
		break;

	case glzPrimitive::ICOSIDODECAHEDRON:
		return glzCountFromIndexArrays(icosidodecahederon_face, sizeof(icosidodecahederon_face) / sizeof(long));
		break;

	case glzPrimitive::FSQ:
		return 6;
		break;
	case glzPrimitive::RANDOM_POINT:
		return (long)pg.resolution_x;
		break;
	case glzPrimitive::SPRITE_ATLAS_ARRAY:
		return pg.tt.atlas_width*pg.tt.atlas_height * 6;
		break;

	default:
		return 0;
		break;

	}
}

long glzVAOMakePrimitive(primitive_gen pg, unsigned int *vao)
{
	if (!isinited_geo_generate) ini_geo_generate();

	unsigned int vaopoint;
	vaopoint = *vao;
	if (glIsVertexArray((GLuint)&vao) == GL_FALSE) glzKillVAO(vaopoint, glzVAOType::AUTO);

	primitive_gen pg2[2];
	pg2[0] = pg;

	long verts = glzVAOMakePrimitives(1, pg2, vao);
	return verts;

}

long glzVAOMakePrimitives(int num, primitive_gen pg[], unsigned int *vao)
{
	if (!isinited_geo_generate) ini_geo_generate();



	unsigned int vaopoint;
	vaopoint = *vao;
	if (glIsVertexArray((GLuint)&vao) == GL_FALSE) glzKillVAO(vaopoint, glzVAOType::AUTO);

	int i = 0;
	long verts = 0;

	while (i<num)
	{
		verts += glzVAOCountPrimitiveVerts(pg[i]);
		i++;
	}



	float *v, *t, *n;
	v = new float[verts * 3];
	t = new float[verts * 2];
	n = new float[verts * 3];




	int curvert = 0;
	int oldcurvert = 0;
	int saic = 0, sai = 0;
	i = 0;
	while (i<num)
	{

		switch (pg[i].type)
		{

		case glzPrimitive::CUBE:
		case glzPrimitive::HEXAHEDRON:
			curvert = glzPrimCubeverts(v + oldcurvert * 3, t + oldcurvert * 2, n + oldcurvert * 3);

			//curvert=glzPrimFromIndexArrays(v+oldcurvert*3,t+oldcurvert*2,n+oldcurvert*3,cube_vertex,cube_uv,cube_normal,cube_face,cube_uvface,cube_nface,sizeof(cube_face)/sizeof(long));
			glzProjectVertexArray(v + oldcurvert * 3, pg[i].matrix, curvert);


			if ((pg[i].tt.atlas_height>1) || (pg[i].tt.atlas_width>1))
			{
				int aw = pg[i].tt.atlas_width;

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
			curvert = glzPrimTetra(v + oldcurvert * 3, t + oldcurvert * 2, n + oldcurvert * 3);
			glzProjectVertexArray(v + oldcurvert * 3, pg[i].matrix, curvert);
			break;


		case glzPrimitive::PYRAMID:
			curvert = glzPrimFromIndexArrays(v + oldcurvert * 3, t + oldcurvert * 2, n + oldcurvert * 3, pyramid_vertex, pyramid_uv, pyramid_normal, pyramid_face, pyramid_uvface, pyramid_nface, sizeof(pyramid_face) / sizeof(long));
			glzProjectVertexArray(v + oldcurvert * 3, pg[i].matrix, curvert);
			break;

		case glzPrimitive::OCTAHEDRON:
			curvert = glzPrimFromIndexArrays(v + oldcurvert * 3, t + oldcurvert * 2, n + oldcurvert * 3, octahedron_vertex, octahedron_uv, octahedron_normal, octahedron_face, octahedron_uvface, octahedron_nface, sizeof(octahedron_face) / sizeof(long));
			glzProjectVertexArray(v + oldcurvert * 3, pg[i].matrix, curvert);
			break;

		case glzPrimitive::DODECAHEDRON:
			curvert = glzPrimFromIndexArrays(v + oldcurvert * 3, t + oldcurvert * 2, n + oldcurvert * 3, dodecahedron_vertex, dodecahedron_uv, dodecahedron_normal, dodecahedron_face, dodecahedron_uvface, dodecahedron_nface, sizeof(dodecahedron_face) / sizeof(long));
			glzProjectVertexArray(v + oldcurvert * 3, pg[i].matrix, curvert);
			break;

		case glzPrimitive::ICOSAHEDRON:
			curvert = glzPrimFromIndexArrays(v + oldcurvert * 3, t + oldcurvert * 2, n + oldcurvert * 3, icosahedron_vertex, icosahedron_uv, icosahedron_normal, icosahedron_face, icosahedron_uvface, icosahedron_nface, sizeof(icosahedron_face) / sizeof(long));
			glzProjectVertexArray(v + oldcurvert * 3, pg[i].matrix, curvert);
			break;

		case glzPrimitive::ICOSIDODECAHEDRON:
			curvert = glzPrimFromIndexArrays(v + oldcurvert * 3, t + oldcurvert * 2, n + oldcurvert * 3, icosidodecahederon_vertex, icosidodecahederon_uv, icosidodecahederon_normal, icosidodecahederon_face, icosidodecahederon_uvface, icosidodecahederon_nface, sizeof(icosidodecahederon_face) / sizeof(long));
			glzProjectVertexArray(v + oldcurvert * 3, pg[i].matrix, curvert);
			break;



		case glzPrimitive::FSQ:
			curvert = glzPrimFSQ(v + oldcurvert * 3, t + oldcurvert * 2, n + oldcurvert * 3);
			break;

		case glzPrimitive::RANDOM_POINT:
			curvert += glzPrimRandom(v + oldcurvert, t + oldcurvert, n + oldcurvert, pg[i].resolution_x);
			glzProjectVertexArray(v + oldcurvert * 3, pg[i].matrix, curvert);
			break;

		case glzPrimitive::SPRITE_ATLAS_ARRAY:

			saic = pg[i].tt.atlas_width*pg[i].tt.atlas_height;

			sai = 0;


			while (sai<saic)
			{
				curvert = glzPrimFSQ(v + oldcurvert * 3, t + oldcurvert * 2, n + oldcurvert * 3);

				glzAtlasUVarrayRemap(sai, 6, pg[i].tt.atlas_width, pg[i].tt.atlas_height, pg[i].tt.origin, t + oldcurvert * 2);
				oldcurvert += curvert;

				sai++;
			}

			oldcurvert -= curvert;
			break;

		default:
			break;

		}

		if ((pg[i].tt.atlas_width + pg[i].tt.atlas_height>2) && (pg[i].type != glzPrimitive::CUBE) && (pg[i].type != glzPrimitive::HEXAHEDRON) && (pg[i].type != glzPrimitive::SPRITE_ATLAS_ARRAY))
		{
			glzAtlasUVarrayRemap(pg[i].tt.firstatlas, curvert, pg[i].tt.atlas_width, pg[i].tt.atlas_height, pg[i].tt.origin, t + oldcurvert * 2);
		}

		oldcurvert += curvert;
		i++;
	}



	glzVAOMakeFromArray(v, t, n, verts, vao, glzVAOType::AUTO);


	delete[] v;
	delete[] t;
	delete[] n;
	v = NULL;
	t = NULL;
	n = NULL;

	return verts;
}
