#version 140


in vec4 txcoord;
out vec4 fragment_color;
uniform sampler2D texunit0; // atlas reference map
uniform sampler2D texunit1; // atlas map


//uniform int width;  // height and width of the atlas reference map
//uniform int height;

//uniform int a_width;  // height and width of the atlas map
//uniform int a_height;

void main() {
        
float sx=0.0;
float sy=0.0;
int width=16;  // height and width of the atlas reference map
int height=16;

int a_width=4;  // height and width of the atlas map
int a_height=4;

vec4 arm = texture2D(texunit0, txcoord.xy);

sx=floor(arm.x*256.0);
sy=floor(arm.y*256.0);

vec2 newtx = vec2(fract(txcoord.x*width),fract(txcoord.y*height));

sy=(a_height-1)-sy;

newtx /= vec2(a_width,a_height);
newtx.x+=(1.0/a_width)*sx;
newtx.y+=(1.0/a_height)*sy;

vec4 am = texture2D(texunit1, newtx.xy);

fragment_color=am;
//fragment_color=vec4(newtx.xy,0.0,1.0);
//fragment_color=vec4(1.0,0.0,0.0,1.0);


}             