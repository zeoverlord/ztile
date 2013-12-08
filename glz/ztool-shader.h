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

// glz shader toolkit - Warning does not produce actual shade
// visit http://www.flashbang.se or contact me at overlord@flashbang.se
// the entire toolkit should exist in it's entirety at github
// https://github.com/zeoverlord/glz.git

#include "ztool-type.h"



		//type signifies the type of data to choose from, if set at GLZ_AUTO it chooses the default settings


unsigned int glzShaderLoad(char file_vert[255], char file_geo[255], char file_frag[255], glzVAOType type);
unsigned int glzShaderLoad(char file_vert[255], char file_frag[255], glzVAOType type);
	void glzShaderLink(unsigned int program);

// for now just call one of the two first ones with "GLZ_AUTO" as the type then the last one, there will be much more here in future versions







