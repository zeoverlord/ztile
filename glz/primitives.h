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

// glz geometry toolkit primitive definitions - you have no idea how anoying this was to make
// visit http://www.flashbang.se or contact me at overlord@flashbang.se
// the entire toolkit should exist in it's entirety at github
// git:// [future home of github link]



// all of these arrays where generated by making a primitive in lightwave then exporting it to .obj
// since that obj file lacks normals i then load it in maya and then export it into a second .obj file
// then i load that obj file into a program called crossroads 3D which is so old that the kid in the baby picture that shows up on load is old enough to drive a car
// but that program is the only one i could find that exports into readable c++ code, i might have to write one myself pretty soon though that cuts out all but the first step

Point3 cube_vertex[] = {
	{ -0.500000, -0.500000,  0.500000}, {  0.500000, -0.500000,  0.500000}, {  0.500000,  0.500000,  0.500000},
	{ -0.500000,  0.500000,  0.500000}, {  0.500000,  0.500000, -0.500000}, { -0.500000,  0.500000, -0.500000},
	{  0.500000, -0.500000, -0.500000}, { -0.500000, -0.500000, -0.500000}
};

long cube_face[] = {
	0,1,2,3,-1,
	3,2,4,5,-1,
	5,4,6,7,-1,
	7,6,1,0,-1,
	1,6,4,2,-1,
	7,0,3,5,-1
};

Point3 cube_normal[] = {
	{  0.000000,  0.000000,  1.000000}, {  0.000000,  1.000000,  0.000000}, {  0.000000,  0.000000, -1.000000},
	{  0.000000, -1.000000,  0.000000}, {  1.000000,  0.000000,  0.000000}, { -1.000000,  0.000000,  0.000000}
};

long cube_nface[] = {
	0,0,0,0,-1,
	1,1,1,1,-1,
	2,2,2,2,-1,
	3,3,3,3,-1,
	4,4,4,4,-1,
	5,5,5,5,-1
};

Point2 cube_uv[] = {
	{  0.000000,  0.000000}, {  1.000000,  0.000000}, {  1.000000,  1.000000},
	{  0.000000,  1.000000}, {  1.000000,  2.000000}, {  0.000000,  2.000000},
	{  1.000000,  3.000000}, {  0.000000,  3.000000}, {  1.000000,  4.000000},
	{  0.000000,  4.000000}, {  2.000000,  0.000000}, {  2.000000,  1.000000},
	{ -1.000000,  0.000000}, { -1.000000,  1.000000}
};

long cube_uvface[] = {
	0,1,2,3,-1,
	0,1,2,3,-1,
	0,1,2,3,-1,
	0,1,2,3,-1,
	0,1,2,3,-1,
	0,1,2,3,-1
};

long cube_uvfaceb[] = {
	0,1,2,3,-1,
	3,2,4,5,-1,
	5,4,6,7,-1,
	7,6,8,9,-1,
	1,10,11,2,-1,
	12,0,3,13,-1
};


Point3 icosidodecahederon_vertex[] = {
	{  0.404509,  0.154509, -0.250000}, {  0.250000,  0.404509, -0.154509}, {  0.250000,  0.404509,  0.154509},
	{  0.404509,  0.154509,  0.250000}, {  0.500000,  0.000000,  0.000000}, {  0.404509, -0.154509,  0.250000},
	{  0.250000, -0.404509,  0.154509}, {  0.250000, -0.404509, -0.154509}, {  0.404509, -0.154509, -0.250000},
	{ -0.404509,  0.154509,  0.250000}, { -0.250000,  0.404509,  0.154509}, { -0.250000,  0.404509, -0.154509},
	{ -0.404509,  0.154509, -0.250000}, { -0.500000,  0.000000,  0.000000}, { -0.404509, -0.154509, -0.250000},
	{ -0.250000, -0.404509, -0.154509}, { -0.250000, -0.404509,  0.154509}, { -0.404509, -0.154509,  0.250000},
	{  0.154509,  0.250000, -0.404509}, { -0.154509,  0.250000, -0.404509}, {  0.000000,  0.500000,  0.000000},
	{ -0.154509,  0.250000,  0.404509}, {  0.154509,  0.250000,  0.404509}, { -0.154509, -0.250000, -0.404509},
	{  0.154509, -0.250000, -0.404509}, {  0.000000, -0.500000,  0.000000}, {  0.154509, -0.250000,  0.404509},
	{ -0.154509, -0.250000,  0.404509}, {  0.000000,  0.000000, -0.500000}, {  0.000000,  0.000000,  0.500000},
	{  0.000000,  0.000000,  0.000000}
};

long icosidodecahederon_face[] = {
	0,1,2,3,4,-1,
	5,6,7,8,4,-1,
	9,10,11,12,13,-1,
	14,15,16,17,13,-1,
	1,18,19,11,20,-1,
	10,21,22,2,20,-1,
	15,23,24,7,25,-1,
	6,26,27,16,25,-1,
	18,0,8,24,28,-1,
	23,14,12,19,28,-1,
	26,5,3,22,29,-1,
	21,9,17,27,29,-1,
	8,0,4,-1,
	3,5,4,-1,
	12,14,13,-1,
	17,9,13,-1,
	2,1,20,-1,
	11,10,20,-1,
	7,6,25,-1,
	16,15,25,-1,
	19,18,28,-1,
	24,23,28,-1,
	22,21,29,-1,
	27,26,29,-1,
	18,1,0,-1,
	2,22,3,-1,
	7,24,8,-1,
	26,6,5,-1,
	11,19,12,-1,
	21,10,9,-1,
	23,15,14,-1,
	16,27,17,-1,
	30,30,30,30,30,-1,
	30,30,30,30,30,-1,
	30,30,30,30,30,-1,
	30,30,30,30,30,-1,
	30,30,30,30,30,-1,
	30,30,30,30,30,-1,
	30,30,30,30,30,-1,
	30,30,30,30,30,-1,
	30,30,30,30,30,-1,
	30,30,30,30,30,-1,
	30,30,30,30,30,-1,
	30,30,30,30,30,-1,
	30,30,30,-1,
	30,30,30,-1,
	30,30,30,-1,
	30,30,30,-1,
	30,30,30,-1,
	30,30,30,-1,
	30,30,30,-1,
	30,30,30,-1,
	30,30,30,-1,
	30,30,30,-1,
	30,30,30,-1,
	30,30,30,-1,
	30,30,30,-1,
	30,30,30,-1,
	30,30,30,-1,
	30,30,30,-1,
	30,30,30,-1,
	30,30,30,-1,
	30,30,30,-1,
	30,30,30,-1
};

Point3 icosidodecahederon_normal[] = {
	{  0.850651,  0.525731,  0.000000}, {  0.850651, -0.525731,  0.000000}, { -0.850651,  0.525731,  0.000000},
	{ -0.850651, -0.525731,  0.000000}, {  0.000000,  0.850651, -0.525731}, {  0.000000,  0.850651,  0.525731},
	{  0.000000, -0.850651, -0.525731}, {  0.000000, -0.850651,  0.525731}, {  0.525731,  0.000000, -0.850651},
	{ -0.525731,  0.000000, -0.850651}, {  0.525731,  0.000000,  0.850651}, { -0.525731,  0.000000,  0.850651},
	{  0.934173,  0.000000, -0.356820}, {  0.934173,  0.000000,  0.356820}, { -0.934173,  0.000000, -0.356820},
	{ -0.934173,  0.000000,  0.356820}, {  0.356820,  0.934173,  0.000000}, { -0.356820,  0.934173,  0.000000},
	{  0.356820, -0.934173,  0.000000}, { -0.356820, -0.934173,  0.000000}, {  0.000000,  0.356820, -0.934173},
	{  0.000000, -0.356820, -0.934173}, {  0.000000,  0.356820,  0.934173}, {  0.000000, -0.356820,  0.934173},
	{  0.577350,  0.577350, -0.577350}, {  0.577350,  0.577350,  0.577350}, {  0.577350, -0.577350, -0.577350},
	{  0.577350, -0.577350,  0.577350}, { -0.577350,  0.577350, -0.577350}, { -0.577350,  0.577350,  0.577350},
	{ -0.577350, -0.577350, -0.577350}, { -0.577350, -0.577350,  0.577350}, {  0.000000,  0.000000,  0.000000}
};

long icosidodecahederon_nface[] = {
	0,0,0,0,0,-1,
	1,1,1,1,1,-1,
	2,2,2,2,2,-1,
	3,3,3,3,3,-1,
	4,4,4,4,4,-1,
	5,5,5,5,5,-1,
	6,6,6,6,6,-1,
	7,7,7,7,7,-1,
	8,8,8,8,8,-1,
	9,9,9,9,9,-1,
	10,10,10,10,10,-1,
	11,11,11,11,11,-1,
	12,12,12,-1,
	13,13,13,-1,
	14,14,14,-1,
	15,15,15,-1,
	16,16,16,-1,
	17,17,17,-1,
	18,18,18,-1,
	19,19,19,-1,
	20,20,20,-1,
	21,21,21,-1,
	22,22,22,-1,
	23,23,23,-1,
	24,24,24,-1,
	25,25,25,-1,
	26,26,26,-1,
	27,27,27,-1,
	28,28,28,-1,
	29,29,29,-1,
	30,30,30,-1,
	31,31,31,-1,
	32,32,32,32,32,-1,
	32,32,32,32,32,-1,
	32,32,32,32,32,-1,
	32,32,32,32,32,-1,
	32,32,32,32,32,-1,
	32,32,32,32,32,-1,
	32,32,32,32,32,-1,
	32,32,32,32,32,-1,
	32,32,32,32,32,-1,
	32,32,32,32,32,-1,
	32,32,32,32,32,-1,
	32,32,32,32,32,-1,
	32,32,32,-1,
	32,32,32,-1,
	32,32,32,-1,
	32,32,32,-1,
	32,32,32,-1,
	32,32,32,-1,
	32,32,25,-1,
	25,26,26,-1,
	26,27,27,-1,
	27,28,28,-1,
	28,29,29,-1,
	29,30,30,-1,
	30,31,31,-1,
	31,32,32,-1,
	32,32,32,-1,
	32,32,32,-1,
	32,32,32,-1,
	32,32,32,-1,
	32,32,32,-1,
	32,32,32,-1
};

Point2 icosidodecahederon_uv[] = {
	{  0.588104,  0.654508}, {  0.588104,  0.904508}, {  0.411896,  0.904508},
	{  0.411896,  0.654508}, {  0.500000,  0.500000}, {  0.411896,  0.345491},
	{  0.411896,  0.095491}, {  0.588104,  0.095491}, {  0.588104,  0.345491},
	{  0.088104,  0.654508}, {  0.088104,  0.904508}, { -0.088104,  0.904508},
	{ -0.088104,  0.654508}, {  0.000000,  0.500000}, { -0.088104,  0.345491},
	{ -0.088104,  0.095491}, {  0.088104,  0.095491}, {  0.088104,  0.345491},
	{  0.691930,  0.750000}, {  0.808070,  0.750000}, {  0.911896,  0.904508},
	{  0.750000,  1.000000}, {  0.191930,  0.750000}, {  0.308070,  0.750000},
	{  0.250000,  1.000000}, {  0.911896,  0.095491}, {  0.808070,  0.250000},
	{  0.691930,  0.250000}, {  0.750000,  0.000000}, {  0.308070,  0.250000},
	{  0.191930,  0.250000}, {  0.250000,  0.000000}, {  0.750000,  0.500000},
	{  0.911896,  0.345491}, {  0.911896,  0.654508}, {  0.250000,  0.500000},
	{  1.000000,  0.500000}, {  0.500000,  1.000000}, {  0.000000,  1.000000},
	{  0.500000,  0.000000}, {  0.000000,  0.000000}
};

long icosidodecahederon_uvface[] = {
	0,1,2,3,4,-1,
	5,6,7,8,4,-1,
	9,10,11,12,13,-1,
	14,15,16,17,13,-1,
	1,18,19,20,21,-1,
	10,22,23,2,24,-1,
	25,26,27,7,28,-1,
	6,29,30,16,31,-1,
	18,0,8,27,32,-1,
	26,33,34,19,32,-1,
	29,5,3,23,35,-1,
	22,9,17,30,35,-1,
	8,0,4,-1,
	3,5,4,-1,
	34,33,36,-1,
	17,9,13,-1,
	2,1,37,-1,
	11,10,38,-1,
	7,6,39,-1,
	16,15,40,-1,
	19,18,32,-1,
	27,26,32,-1,
	23,22,35,-1,
	30,29,35,-1,
	18,1,0,-1,
	2,23,3,-1,
	7,27,8,-1,
	29,6,5,-1,
	20,19,34,-1,
	22,10,9,-1,
	26,25,33,-1,
	16,30,17,-1,
	40,40,40,40,40,-1,
	40,40,40,40,40,-1,
	40,40,40,40,40,-1,
	40,40,40,40,40,-1,
	40,40,40,40,40,-1,
	40,40,40,40,40,-1,
	40,40,40,40,40,-1,
	40,40,40,40,40,-1,
	40,40,40,40,40,-1,
	40,40,40,40,40,-1,
	40,40,40,40,40,-1,
	40,40,40,40,40,-1,
	40,40,40,-1,
	40,40,40,-1,
	40,40,40,-1,
	40,40,40,-1,
	40,40,40,-1,
	40,40,40,-1,
	40,40,23,-1,
	3,7,27,-1,
	8,29,6,-1,
	5,20,19,-1,
	34,22,10,-1,
	9,26,25,-1,
	33,16,30,-1,
	17,40,40,-1,
	40,40,40,-1,
	40,40,40,-1,
	40,40,40,-1,
	40,40,40,-1,
	40,40,40,-1,
	40,40,40,-1
};

Point3 icosahedron_vertex[] = {
	{  0.262866,  0.000000, -0.425325}, { -0.262866,  0.000000, -0.425325}, {  0.000000,  0.425325, -0.262866},
	{  0.425325,  0.262866,  0.000000}, {  0.425325, -0.262866,  0.000000}, {  0.000000, -0.425325, -0.262866},
	{ -0.425325, -0.262866,  0.000000}, { -0.425325,  0.262866,  0.000000}, {  0.000000,  0.425325,  0.262866},
	{  0.000000, -0.425325,  0.262866}, { -0.262866,  0.000000,  0.425325}, {  0.262866,  0.000000,  0.425325}
};

long icosahedron_face[] = {
	0,1,2,-1,
	3,0,2,-1,
	3,4,0,-1,
	0,4,5,-1,
	1,0,5,-1,
	6,1,5,-1,
	6,7,1,-1,
	1,7,2,-1,
	7,8,2,-1,
	8,3,2,-1,
	9,6,5,-1,
	4,9,5,-1,
	10,11,8,-1,
	11,3,8,-1,
	4,3,11,-1,
	4,11,9,-1,
	11,10,9,-1,
	10,6,9,-1,
	7,6,10,-1,
	7,10,8,-1
};

Point3 icosahedron_normal[] = {
	{  0.000000,  0.356821, -0.934173}, {  0.577350,  0.577350, -0.577350}, {  0.934173,  0.000000, -0.356821},
	{  0.577350, -0.577350, -0.577350}, {  0.000000, -0.356821, -0.934173}, { -0.577350, -0.577350, -0.577350},
	{ -0.934173,  0.000000, -0.356821}, { -0.577350,  0.577350, -0.577350}, { -0.356821,  0.934173,  0.000000},
	{  0.356821,  0.934173,  0.000000}, { -0.356821, -0.934173,  0.000000}, {  0.356821, -0.934173,  0.000000},
	{  0.000000,  0.356821,  0.934173}, {  0.577350,  0.577350,  0.577350}, {  0.934173,  0.000000,  0.356821},
	{  0.577350, -0.577350,  0.577350}, {  0.000000, -0.356821,  0.934173}, { -0.577350, -0.577350,  0.577350},
	{ -0.934173,  0.000000,  0.356821}, { -0.577350,  0.577350,  0.577350}
};

long icosahedron_nface[] = {
	0,0,0,-1,
	1,1,1,-1,
	2,2,2,-1,
	3,3,3,-1,
	4,4,4,-1,
	5,5,5,-1,
	6,6,6,-1,
	7,7,7,-1,
	8,8,8,-1,
	9,9,9,-1,
	10,10,10,-1,
	11,11,11,-1,
	12,12,12,-1,
	13,13,13,-1,
	14,14,14,-1,
	15,15,15,-1,
	16,16,16,-1,
	17,17,17,-1,
	18,18,18,-1,
	19,19,19,-1
};

Point2 icosahedron_uv[] = {
	{  0.661896,  0.500000}, {  0.838104,  0.500000}, {  0.750000,  1.000000},
	{  0.500000,  0.809017}, {  0.500000,  0.190983}, {  0.750000,  0.000000},
	{  1.000000,  0.190983}, {  1.000000,  0.809017}, {  0.250000,  1.000000},
	{  0.250000,  0.000000}, {  0.161896,  0.500000}, {  0.338104,  0.500000},
	{  0.000000,  0.190983}, {  0.000000,  0.809017}
};

long icosahedron_uvface[] = {
	0,1,2,-1,
	3,0,2,-1,
	3,4,0,-1,
	0,4,5,-1,
	1,0,5,-1,
	6,1,5,-1,
	6,7,1,-1,
	1,7,2,-1,
	7,8,2,-1,
	8,3,2,-1,
	9,6,5,-1,
	4,9,5,-1,
	10,11,8,-1,
	11,3,8,-1,
	4,3,11,-1,
	4,11,9,-1,
	11,10,9,-1,
	10,12,9,-1,
	13,12,10,-1,
	13,10,8,-1
};

Point3 dodecahedron_vertex[] = {
	{  0.288675,  0.288675, -0.288675}, {  0.467086,  0.000000, -0.178411}, {  0.288675, -0.288675, -0.288675},
	{  0.000000, -0.178411, -0.467086}, {  0.000000,  0.178411, -0.467086}, { -0.288675,  0.288675, -0.288675},
	{ -0.178411,  0.467086,  0.000000}, {  0.178411,  0.467086,  0.000000}, { -0.288675, -0.288675, -0.288675},
	{ -0.467086,  0.000000, -0.178411}, {  0.178411, -0.467086,  0.000000}, { -0.178411, -0.467086,  0.000000},
	{  0.288675, -0.288675,  0.288675}, {  0.467086,  0.000000,  0.178411}, {  0.288675,  0.288675,  0.288675},
	{  0.000000,  0.178411,  0.467086}, {  0.000000, -0.178411,  0.467086}, { -0.288675, -0.288675,  0.288675},
	{ -0.288675,  0.288675,  0.288675}, { -0.467086,  0.000000,  0.178411}
};

long dodecahedron_face[] = {
	0,1,2,3,4,-1,
	5,6,7,0,4,-1,
	3,8,9,5,4,-1,
	2,10,11,8,3,-1,
	12,13,14,15,16,-1,
	17,11,10,12,16,-1,
	15,18,19,17,16,-1,
	14,7,6,18,15,-1,
	13,12,10,2,1,-1,
	0,7,14,13,1,-1,
	19,18,6,5,9,-1,
	8,11,17,19,9,-1
};

Point3 dodecahedron_normal[] = {
	{  0.525731,  0.000000, -0.850651}, {  0.000000,  0.850651, -0.525731}, { -0.525731,  0.000000, -0.850651},
	{  0.000000, -0.850651, -0.525731}, {  0.525731,  0.000000,  0.850651}, {  0.000000, -0.850651,  0.525731},
	{ -0.525731, -0.000000,  0.850651}, {  0.000000,  0.850651,  0.525731}, {  0.850651, -0.525731, -0.000000},
	{  0.850651,  0.525731,  0.000000}, { -0.850651,  0.525731, -0.000000}, { -0.850651, -0.525731,  0.000000}
};

long dodecahedron_nface[] = {
	0,0,0,0,0,-1,
	1,1,1,1,1,-1,
	2,2,2,2,2,-1,
	3,3,3,3,3,-1,
	4,4,4,4,4,-1,
	5,5,5,5,5,-1,
	6,6,6,6,6,-1,
	7,7,7,7,7,-1,
	8,8,8,8,8,-1,
	9,9,9,9,9,-1,
	10,10,10,10,10,-1,
	11,11,11,11,11,-1
};

Point2 dodecahedron_uv[] = {
	{  0.001907,  0.096738}, {  0.155210,  0.001992}, {  0.308512,  0.096738},
	{  0.249956,  0.250041}, {  0.060463,  0.250041}, {  0.315558,  0.403343},
	{  0.374114,  0.250041}, {  0.563607,  0.250041}, {  0.622163,  0.403343},
	{  0.468860,  0.498089}, {  0.308512,  0.403343}, {  0.155210,  0.498089},
	{  0.001907,  0.403343}, {  0.629022,  0.403343}, {  0.687578,  0.250041},
	{  0.877071,  0.250041}, {  0.935627,  0.403343}, {  0.782325,  0.498089},
	{  0.648853,  0.596657}, {  0.802155,  0.501911}, {  0.955458,  0.596657},
	{  0.896901,  0.749959}, {  0.707409,  0.749959}, {  0.935627,  0.096738},
	{  0.629022,  0.096738}, {  0.782325,  0.001992}, {  0.955458,  0.903262},
	{  0.802155,  0.998008}, {  0.648853,  0.903262}, {  0.622163,  0.096738},
	{  0.315558,  0.096738}, {  0.468860,  0.001992}, {  0.394930,  0.749959},
	{  0.336374,  0.596657}, {  0.489677,  0.501911}, {  0.642979,  0.596657},
	{  0.584423,  0.749959}, {  0.642979,  0.903262}, {  0.489677,  0.998008},
	{  0.336374,  0.903262}, {  0.271944,  0.749959}, {  0.330500,  0.903262},
	{  0.177198,  0.998008}, {  0.023896,  0.903262}, {  0.082452,  0.749959},
	{  0.023896,  0.596657}, {  0.177198,  0.501911}, {  0.330500,  0.596657}
};

long dodecahedron_uvface[] = {
	0,1,2,3,4,-1,
	5,6,7,8,9,-1,
	3,10,11,12,4,-1,
	13,14,15,16,17,-1,
	18,19,20,21,22,-1,
	23,15,14,24,25,-1,
	21,26,27,28,22,-1,
	29,7,6,30,31,-1,
	32,33,34,35,36,-1,
	37,38,39,32,36,-1,
	40,41,42,43,44,-1,
	45,46,47,40,44,-1
};

Point3 octahedron_vertex[] = {
	{  0.000000,  0.000000, -0.500000}, {  0.000000,  0.500000,  0.000000}, {  0.500000,  0.000000,  0.000000},
	{  0.000000,  0.000000,  0.500000}, {  0.000000, -0.500000,  0.000000}, { -0.500000,  0.000000,  0.000000}
};

long octahedron_face[] = {
	0,1,2,-1,
	1,3,2,-1,
	4,0,2,-1,
	3,4,2,-1,
	1,0,5,-1,
	3,1,5,-1,
	0,4,5,-1,
	4,3,5,-1
};

Point3 octahedron_normal[] = {
	{  0.577350,  0.577350, -0.577350}, {  0.577350,  0.577350,  0.577350}, {  0.577350, -0.577350, -0.577350},
	{  0.577350, -0.577350,  0.577350}, { -0.577350,  0.577350, -0.577350}, { -0.577350,  0.577350,  0.577350},
	{ -0.577350, -0.577350, -0.577350}, { -0.577350, -0.577350,  0.577350}
};

long octahedron_nface[] = {
	0,0,0,-1,
	1,1,1,-1,
	2,2,2,-1,
	3,3,3,-1,
	4,4,4,-1,
	5,5,5,-1,
	6,6,6,-1,
	7,7,7,-1
};

Point2 octahedron_uv[] = {
	{  0.750000,  0.500000}, {  0.625000,  1.000000}, {  0.500000,  0.500000},
	{  0.375000,  1.000000}, {  0.250000,  0.500000}, {  0.625000,  0.000000},
	{  0.375000,  0.000000}, {  0.875000,  1.000000}, {  1.000000,  0.500000},
	{  0.125000,  1.000000}, {  0.000000,  0.500000}, {  0.875000,  0.000000},
	{  0.125000,  0.000000}
};

long octahedron_uvface[] = {
	0,1,2,-1,
	3,4,2,-1,
	5,0,2,-1,
	4,6,2,-1,
	7,0,8,-1,
	4,9,10,-1,
	0,11,8,-1,
	12,4,10,-1
};


Point3 pyramid_vertex[] = {
	{ -0.441007, -0.311839, -0.441007}, {  0.441007, -0.311839, -0.441007}, {  0.441007, -0.311839,  0.441007},
	{ -0.441007, -0.311839,  0.441007}, {  0.000000,  0.311839,  0.000000}
};

long pyramid_face[] = {
	0,1,2,3,-1,
	0,3,4,-1,
	3,2,4,-1,
	2,1,4,-1,
	1,0,4,-1
};

Point3 pyramid_normal[] = {
	{  0.000000, -1.000000,  0.000000}, { -0.816497,  0.577350, -0.000000}, {  0.000000,  0.577350,  0.816497},
	{  0.816497,  0.577350,  0.000000}, { -0.000000,  0.577350, -0.816497}
};

long pyramid_nface[] = {
	0,0,0,0,-1,
	1,1,1,-1,
	2,2,2,-1,
	3,3,3,-1,
	4,4,4,-1
};

Point2 pyramid_uv[] = {
	{  0.002890,  0.501453}, {  0.500591,  0.999489}, {  0.998923,  0.501463},
	{  0.500591,  0.001714}, {  0.002892,  0.001715}, {  0.998912,  0.001714},
	{  0.500591,  0.999490}, {  0.998911,  0.999407}, {  0.002891,  0.501453},
	{  0.500573,  0.999490}, {  0.002901,  0.999490}
};

long pyramid_uvface[] = {
	0,1,2,3,-1,
	3,0,4,-1,
	2,3,5,-1,
	6,2,7,-1,
	8,9,10,-1
};
