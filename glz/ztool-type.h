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

// common glz typedefs
// visit http://www.flashbang.se or contact me at overlord@flashbang.se
// the entire toolkit should exist in it's entirety at github
// https://github.com/zeoverlord/glz.git

#include <vector>

using namespace std;


#ifndef __glztype__
#define __glztype__


enum class glzVAOType { AUTO, VERTEX, VERTEX_TEXTURE, VERTEX_NORMAL, VERTEX_TEXTURE_NORMAL };
enum class glzOrigin { BOTTOM_LEFT, BOTTOM_RIGHT, TOP_LEFT, TOP_RIGHT, CENTERED };
enum class glzAxis { X, Y, Z };

enum class glzTexFilter { NONE, NEAREST, LINEAR, BILINEAR, TRILINEAR, ANSIO_2, ANSIO_4, ANSIO_8, ANSIO_16, ANSIO_MAX };
enum class glzTexCompression { UNCOMPRESSED, COMPRESSED };


enum class glzColorChannels { RED, GREEN, BLUE, ALPHA, HUE, HUE2, CROMA, CROMA2, VALUE, LIGHTNESS, INTENSITY, LUMA, SHSV, SHSL, SHSI };
enum class glzColorType { RGB_8, RGB_32F, RGBA_8, RGBA_32F, HSL_8, HSL_32F, HSV_8, HSV_32F, HSI_8, HSI_32F, HCY_8, HCY_32F };


enum class glzPrimitive {
	CUBE, SPHERE, PYRAMID, TETRAHEDRON, HEXAHEDRON, OCTAHEDRON, DODECAHEDRON, ICOSAHEDRON, ICOSIDODECAHEDRON, TORUS,		// basic shapes - sphere and torus not implemented
	GEODESIC_TETRA, GEODESIC_HEXA, GEODESIC_OCTA, GEODESIC_DODECA, GEODESIC_ICOSA,										// geodesics - not implemented
	DOME, DISC, CYLINDER, STAR_DODECAHEDRON,																			// other shapes - not implemented
	FSQ, RANDOM_POINT, SPRITE_ATLAS_ARRAY																				// random structures
};


enum class glzIGTType { NONE, DISPLACE_ADD };

enum class glzTTType { NONE, VERTEX_COORD_ADOPT, ATLASARRAY, ATLAS_CUBE_TBS, ATLAS_CUBE_INDFACE, ATLAS_CUBE_CROSS };

enum class glzSceneGraphType { 
	NONE,			// shouldn't really exist
	DELETABLE,		// to be deleted before next round
	DECORATION,		// contains no interaction only rendering
	STATIC,			// does not move but may hurt player and/or recive damage
	PLAYER,			// remote controlled by the user
	ENTETY,			// has movement but no AI
	STATIC_ENEMY,	// has AI but no movement
	ENEMY			// freemoving enemy with AI
};

enum class glzSceneGraphSubType {
	NONE

};

enum class glzSceneGraphSubMessage {
	NONE, MOVE, PLAYER_MOVE, DAMAGE

};

typedef struct{
	float x_pos, y_pos;
	float x_vec, y_vec;  // motion vector in units per second
	float u, v;
	float age;  // how old this particle is, affects the u texture coordinate
	float maxage; //when to die
	float drag; // how much it's effected by drag
	float gravity;
	float noise;
}glzSimple2DParticle;

class glzSimple2DParticleSystem{
private: 
	
	float gx, gy;	
	float scale;
	bool running;
	unsigned int pc;
	vector<glzSimple2DParticle> p;

public:
	glzSimple2DParticleSystem();
	void set_environment(float gx_in, float gy_in, float scale_in);
	void spawn_burst(unsigned int num, float x_in, float y_in, float v_in, float mag, float maxage_in, float agediff, float drag_in, float dragdiff, float gravity, float noise_in);
	bool run(float t);
	void render_out();
};

// todo, move to own cpp file



// units - well at least it's a beginning, will continue at a later date, probably will be rewritten once visual studio gets user defined literals


class glzsecond;
class glzlength;
class glzspeed;


class glzsecond{ //time in secconds
	double S;

public:
	glzsecond(double sec) : S(sec) {}
	double get() { return S; }
	double glzsecond::operator= (glzsecond b) { return b.get(); }
};

class glzlength{ // length in meters
	double L;

public:
	glzlength(double meter) : L(meter) {}
	double get() { return L; }
	double glzlength::operator= (glzlength b) { return b.get(); }

	glzspeed glzlength::operator/ (glzsecond b);
};

class glzspeed{ // speed in meters per second
	double S;

public:
	glzspeed(double mps) : S(mps) {}
	double get() { return S; }
	double glzspeed::operator= (glzspeed b) { return b.get(); }

	
};


#endif /* __glztype__ */
