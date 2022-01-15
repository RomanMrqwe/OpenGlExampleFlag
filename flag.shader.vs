#version 330 core
layout(location=0)in vec3 aPos;
layout(location=1)in vec3 aTexCoord;//layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform float sinewave;

uniform float framenum;

// uniform sampler2D texture2;

float testf1(float frame){
	return sin(frame*.01)/5.;
}

/////

///// * vec3 wave (vec3 p, vec2 Direction = vec2(1.0,1.0), float pi1 = 3.14, float Wavelength = 1.0, float Speed = 1.0, float Amplitude = 0.1,
/////float Steepness = 0.15)
/// ?use aPos.x or aPos parameter; use direction or direction from framenum
vec3 wave(vec3 Pos,bool UseXZ,vec2 Direction){

float pi1=3.14;
float Wavelength=1.;
float Speed=1.;
///framenum
float Amplitude=.1;

/////

float Steepness=.15;

/////

// vec2 Direction = vec2(1.0,1.0); /// first val p.x -> aPos != 0  //vec2(1.0,1.0);

// from framenum:
if(Direction==vec2(0.,0.)){
	
	Direction=vec2(1.,sin(framenum*.001));/// first val p.x -> aPos != 0  //vec2(1.0,1.0);
	// vec2 Direction = vec2(1.0,testf1(framenum)); /// first val p.x -> aPos != 0  //vec2(1.0,1.0);
	
}

/////

vec3 p=vec3(0.,0.,0.);

if(UseXZ==true){
	
	p=Pos;
	
}else{
	
	p.x=Pos.x;
	
}

float grav=9.8;
///fix speed
grav=.0001;

float k=2*pi1/Wavelength;
float c=sqrt(grav/k);/// float c = sqrt(9.8 / k);
vec2 d=normalize(Direction);
float f=k*(dot(d,p.xz)-c*framenum);

float a=Steepness/k;
// p.x = a * cos(f); ///?+= store prev p.x?
// p.y = a * sin(f);
// p.z = a * cos(f); ///?+= store prev p.x?

p.x=d.x*(a*cos(f));///+=
p.y=a*sin(f);
p.z=p.z+d.y*(a*cos(f));///+=

return p;

}

/////

///rotation around y axis
// float angle1 = 30;

// float rx = cos(angle1)*(aPos.x)+sin(angle1)*(aPos.z);
// float rz = -sin(angle1)*(aPos.x)+cos(angle1)*(aPos.z);

vec3 rotatearoundyaxis(vec3 Pos,float angle1){

float rx=cos(angle1)*(Pos.x)+sin(angle1)*(Pos.z);
float rz=-sin(angle1)*(Pos.x)+cos(angle1)*(Pos.z);

return vec3(rx,Pos.y,rz);

}

/////

void main()
{

float wave=3.;

float amplitude=.25;

vec2 startPos;
startPos.x=-1.;
startPos.y=-1.;

float speed=3.;

float textureWidth=100.;
// float angleSpanH = 10.0;

float angleSpanH=wave*3.14159265;

vec4 a_position=vec4(aPos,0.);

// float pz = amplitude * sin (speed - (a_position.x-startPos.x + a_position.y-startPos.y) / textureWidth * angleSpanH);

float pz=amplitude*sin(sinewave*speed-(a_position.x-startPos.x+a_position.y-startPos.y)/textureWidth*angleSpanH);

/////
float sinewave1=sin(framenum*.001)/10;

// sinewave1
// return (val - min) / (max - min);

float min1=aPos.x-sinewave-.3;
float max1=aPos.x+sinewave+.3;

float zoffset=0.;

sinewave1=((sinewave-min1)/(max1-min1)-2)*2-1.;

/// 1 - abs(sinewave1) -> -1 = 0, 0 = 1, 1 = 0

float phase1=framenum*.0001;
float offset1=(aPos.x+(aPos.z*.2))*.5;
float offsety=sin(phase1+offset1)*.2;

// can mul zoffset by size of wave
float xmin=sinewave-.3;
float xmax=sinewave+.3;
float xhalfway=sinewave;// xmin+0.3

float xzoffset=1.;

if(aPos.x<=xhalfway){
	
	xzoffset=(aPos.x-xmin)/(xmax-xmin);
	
}

if(aPos.x>=xhalfway){
	
	xzoffset=(aPos.x-xmax)/(xmin-xmax);
	
}

float P=aPos.x;///z
float C=sinewave;
float R=.05;

R=xzoffset;

float V=P-C;

float Ps=C+V/length(V)*R;

float pi1=3.14;
float Wavelength=1.;
float Speed=1.;
///framenum
float Amplitude=.1;

/////

float Steepness=.15;

/////

vec2 Direction=vec2(1.,sin(framenum*.001));/// first val p.x -> aPos != 0  //vec2(1.0,1.0);

/////

/////

vec3 p=vec3(0.,0.,0.);
p.x=aPos.x;
float grav=9.8;
///fix speed
grav=.0001;

float k=2*pi1/Wavelength;
float c=sqrt(grav/k);/// float c = sqrt(9.8 / k);
vec2 d=normalize(Direction);
float f=k*(dot(d,p.xz)-c*framenum);

float a=Steepness/k;

p.x=d.x*(a*cos(f));///+=
p.y=a*sin(f);
p.z=p.z+d.y*(a*cos(f));///+=

/////

vec3 wavep1=wave(aPos.xyz,false,vec2(0.,0.));
vec3 wavep2=wave(aPos.xyz,true,vec2(1.,1.));

///WithRotation
//vec3 rotatearoundyaxis (vec3 Pos, float angle1)
vec3 aPosRotated=rotatearoundyaxis(vec3(aPos.x+wavep1.x+wavep2.x/5,aPos.y+wavep1.y+wavep2.y/5,aPos.z+wavep1.z+wavep2.z/5),-.1*sin(framenum*.001));
gl_Position=projection*view*model*vec4(aPosRotated,1.f);//aPos.y+offsety aPos.z

///Withoutrotation
///gl_Position = projection * view * model * vec4(aPos.x+wavep1.x+wavep2.x/5, aPos.y+wavep1.y+wavep2.y/5, aPos.z+wavep1.z+wavep2.z/5, 1.0f); //aPos.y+offsety aPos.z

// gl_Position = projection * view * model * vec4(aPos.x, aPos.y, Ps, 1.0f);

TexCoord=vec2(aTexCoord.x,aTexCoord.y);

}

// Flag can moveon start axis on sine wave and lerp pattern
// rotate all vertexes around axis

// Can combine waves+current result