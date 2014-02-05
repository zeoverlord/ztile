
using namespace std;

#include "ztool-type.h"
#include "ztool-glz.h"
#include "ztool-geo.h"




glzSimpleParticleSystem::glzSimpleParticleSystem()
{
	gx = 0.0f;
	gy = -9.82f;
	gz = 0.0f;
	scale = 100.0f;
	running = false;
	pc = 0;
}

void glzSimpleParticleSystem::set_environment(float gx_in, float gy_in, float gz_in, float scale_in)
{
	gx = gx_in;
	gy = gy_in;	
	gz = gz_in;
	scale = scale_in;
	clampx = false;
	clampy = false;
	clampz = false;
}

void glzSimpleParticleSystem::set_clamp(bool clampx_in, bool clampy_in, bool clampz_in)
{
	clampx = clampx_in;
	clampy = clampy_in;
	clampz = clampz_in;
}

void glzSimpleParticleSystem::spawn_burst(unsigned int num, float x_in, float y_in, float z_in, float v_in, float mag, float maxage_in, float agediff, float drag_in, float dragdiff, float gravity, float noise_in)
{

	unsigned int i = 0;

	float vx = 0, vy = 0, vz = 0, vm = 0, vm2 = 0, xp,yp,zp;

	running = true;

	while (i < num) {
		if (pc >= 20000) return;


		vx = glzRandfs();
		vy = glzRandfs();
		vz = glzRandfs();

		xp = x_in + glzRandfs() * 5;
		yp = y_in + glzRandfs() * 5;
		zp = z_in + glzRandfs() * 5;

		if (clampx) { xp = x_in;  vx = 0.0f; }
		if (clampy) { yp = y_in;  vy = 0.0f; }
		if (clampz) { zp = z_in;  vz = 0.0f; }


		vm = sqrt(vx*vx + vy*vy + vz*vz);
		vm2 = glzRandfs()*mag*scale;
		vx /= vm;
		vy /= vm;
		vz /= vm;
		vx *= vm2;
		vy *= vm2;	
		vz *= vm2;

	
		p.push_back({ xp, yp, zp, vx, vy, vz, 0.0f, v_in, 0.0f - glzRandf()*agediff, maxage_in + glzRandf()*agediff, drag_in + glzRandfs()*dragdiff, ((glzRandf() / 2) + 0.5f)*gravity, noise_in, false });
		i++;
		pc++;
	}

	
	return;
}


bool glzSimpleParticleSystem::run(float t)
{
	if (!running) return false;

	if (p.empty()) { p.clear(); running = false; pc = 0; return false; }
	int i2 = 0;

	// advance age

	auto i = p.begin();
	i2 = 0; // o yes this is way uggly, but i think it woks
	while (i < p.end()) {

		p[i2].age += t;

		if (p[i2].age >= p[i2].maxage)	p[i2].active = false;
		else if (p[i2].age < 0.0f) p[i2].active = false;
		else  p[i2].active = true;

			++i;
			i2++;
		

	}

// cause drag
	i = p.begin();
	i2 = 0; // o yes this is way uggly, but i think it woks
	while (i < p.end()) {

		if (p[i2].active)
		{
			if (!clampx) p[i2].x_vec *= 1 - (p[i2].drag*t);
			if (!clampy) p[i2].y_vec *= 1 - (p[i2].drag*t);
			if (!clampz) p[i2].z_vec *= 1 - (p[i2].drag*t);
		}
		
		++i;
		i2++;
	}

	// gravity
	i = p.begin();
	i2 = 0; // o yes this is way uggly, but i think it woks
	while (i < p.end()) {

		if (p[i2].active)
		{
			if (!clampx) p[i2].x_vec += gx*t*scale*p[i2].gravity;
			if (!clampy) p[i2].y_vec += gy*t*scale*p[i2].gravity;
			if (!clampz) p[i2].z_vec += gz*t*scale*p[i2].gravity;
		}

		++i;
		i2++;
	}



	// noise
	i = p.begin();
	i2 = 0; // o yes this is way uggly, but i think it woks
	while (i < p.end()) {

		if (p[i2].active)
		{
			if (!clampx) p[i2].x_vec += t*scale*p[i2].noise*glzRandfs();
			if (!clampy) p[i2].y_vec += t*scale*p[i2].noise*glzRandfs();
			if (!clampz) p[i2].z_vec += t*scale*p[i2].noise*glzRandfs();
		}

		++i;
		i2++;
	}



	// set u

	i = p.begin();
	i2 = 0; // o yes this is way uggly, but i think it woks
	while (i < p.end()) {

		if (p[i2].active)
		{
			p[i2].u = p[i2].age / p[i2].maxage;
			if (p[i2].u > 0.99f) p[i2].u = 0.99f;
		}

	++i;
	i2++;
	}

	// kill

	 i = p.begin();
	 i2 = 0; // o yes this is way uggly, but i think it woks
	 while (i < p.end()) {

		 if ((!p[i2].active) && (p[i2].age >0.0f))
		 {
			i = p.erase(i);
			pc--;
		 }
		else {
		++i;
		i2++;
		}
	
	}

	//move

	i = p.begin();
	i2 = 0; // o yes this is way uggly, but i think it woks
	while (i < p.end()) {
		
		if (p[i2].active)
		{
			if (!clampx) p[i2].x_pos += p[i2].x_vec*t;
			if (!clampy) p[i2].y_pos += p[i2].y_vec*t;
			if (!clampz) p[i2].z_pos += p[i2].z_vec*t;
		}



		++i;
		i2++;


	}


	return true;
}

void glzSimpleParticleSystem::render_out(void)
{

	if (!running) return;

	float v[60000];
	float t[60000];



	int i3 = 0; // o yes this is way uggly, but i think it woks


	auto i = std::begin(p);
	int i2 = 0; // o yes this is way uggly, but i think it woks
	while (i != std::end(p)) {


		if ((p[i2].active) && (i3 < 20000))
		{
			v[i3 * 3 + 0] = p[i2].x_pos;
			v[i3 * 3 + 1] = p[i2].y_pos;
			v[i3 * 3 + 2] = p[i2].z_pos;

			t[i3 * 2 + 0] = p[i2].u;
			t[i3 * 2 + 1] = p[i2].v;

			i3++;
			
		}
		++i;
		i2++;
}


	glzDirectPointArrayRender(v, t, i3);

}


void glzMatrix::LoadIdentity(void)
{
	double b[] = { 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0 };
	int v[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15}; 
	for (auto i : v ) 
		m[i] = b[i]; 

	return;
}

void glzMatrix::LoadIdentityzero(void)
{
	double b[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
	int v[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
	for (auto i : v)
		m[i] = b[i];

	return;
}



glzMatrix glzMatrix::operator*= (glzMatrix b)
{
	glzMatrix  a(m); 
	int v[] = { 0, 1, 2, 3};

	for (auto i : v){  //Cycle through each vector of first matrix.
		m[i * 4 + 0] = b.m[i * 4] * a.m[0] + b.m[i * 4 + 1] * a.m[4] + b.m[i * 4 + 2] * a.m[8] + b.m[i * 4 + 3] * a.m[12];
		m[i * 4 + 1] = b.m[i * 4] * a.m[1] + b.m[i * 4 + 1] * a.m[5] + b.m[i * 4 + 2] * a.m[9] + b.m[i * 4 + 3] * a.m[13];
		m[i * 4 + 2] = b.m[i * 4] * a.m[2] + b.m[i * 4 + 1] * a.m[6] + b.m[i * 4 + 2] * a.m[10] + b.m[i * 4 + 3] * a.m[14];
		m[i * 4 + 3] = b.m[i * 4] * a.m[3] + b.m[i * 4 + 1] * a.m[7] + b.m[i * 4 + 2] * a.m[11] + b.m[i * 4 + 3] * a.m[15];
	}


	return glzMatrix(m);
}


void glzMatrix::transferMatrix(float *b)
{
	int v[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
	for (auto i : v)
		b[i] = (float)m[i];
}

void glzMatrix::translate(double x, double y, double z)
{
	glzMatrix b;

	b.m[0] = 1;
	b.m[1] = 0;
	b.m[2] = 0;
	b.m[3] = 0;

	b.m[4] = 0;
	b.m[5] = 1;
	b.m[6] = 0;
	b.m[7] = 0;

	b.m[8] = 0;
	b.m[9] = 0;
	b.m[10] = 1;
	b.m[11] = 0;

	b.m[12] = x;
	b.m[13] = y;
	b.m[14] = z;
	b.m[15] = 1;

	this->multThis(b);
	return;

}

void glzMatrix::rotate(double a, double x, double y, double z)
{

	double angle = a*PI_OVER_180;
	glzMatrix b;

	b.m[0] = 1 + (1 - cos(angle))*(x*x - 1);
	b.m[1] = -z*sin(angle) + (1 - cos(angle))*x*y;
	b.m[2] = y*sin(angle) + (1 - cos(angle))*x*z;
	b.m[3] = 0;

	b.m[4] = z*sin(angle) + (1 - cos(angle))*x*y;
	b.m[5] = 1 + (1 - cos(angle))*(y*y - 1);
	b.m[6] = -x*sin(angle) + (1 - cos(angle))*y*z;
	b.m[7] = 0;

	b.m[8] = -y*sin(angle) + (1 - cos(angle))*x*z;
	b.m[9] = x*sin(angle) + (1 - cos(angle))*y*z;
	b.m[10] = 1 + (1 - cos(angle))*(z*z - 1);
	b.m[11] = 0;

	b.m[12] = 0;
	b.m[13] = 0;
	b.m[14] = 0;
	b.m[15] = 1;

	this->multThis(b);

	return;
}

void glzMatrix::perspective(double fov, double aspect, double zNear, double zFar)
{
	const double h = 1.0f / tan(fov*PI_OVER_360);
	double neg_depth = zNear - zFar;

	glzMatrix b;

	b.m[0] = h / aspect;
	b.m[1] = 0;
	b.m[2] = 0;
	b.m[3] = 0;

	b.m[4] = 0;
	b.m[5] = h;
	b.m[6] = 0;
	b.m[7] = 0;

	b.m[8] = 0;
	b.m[9] = 0;
	b.m[10] = (zFar + zNear) / neg_depth;
	b.m[11] = -1;

	b.m[12] = 0;
	b.m[13] = 0;
	b.m[14] = 2.0f*(zNear*zFar) / neg_depth;
	b.m[15] = 0;

	this->multThis(b);

	return;

}

void glzMatrix::ortho(double left, double right, double bottom, double top, double Znear, double Zfar)
{

	glzMatrix b;

	b.m[0] = 2 / (right - left);
	b.m[1] = 0;
	b.m[2] = 0;
	b.m[3] = -((right + left) / (right - left));

	b.m[4] = 0;
	b.m[5] = 2 / (top - bottom);
	b.m[6] = 0;
	b.m[7] = -((top + bottom) / (top - bottom));

	b.m[8] = 0;
	b.m[9] = 0;
	b.m[10] = 2 / (Zfar - Znear);
	b.m[11] = -((Zfar + Znear) / (Zfar - Znear));

	b.m[12] = 0;
	b.m[13] = 0;
	b.m[14] = 0;
	b.m[15] = 1;

	this->multThis(b);

	return;
}


void glzMatrix::ortho2D(double left, double right, double bottom, double top)
{

	double Znear = -1.0f, Zfar = 1.0f;
	glzMatrix b;

	b.m[0] = 2 / (right - left);
	b.m[1] = 0;
	b.m[2] = 0;
	b.m[3] = -((right + left) / (right - left));

	b.m[4] = 0;
	b.m[5] = 2 / (top - bottom);
	b.m[6] = 0;
	b.m[7] = -((top + bottom) / (top - bottom));

	b.m[8] = 0;
	b.m[9] = 0;
	b.m[10] = 2 / (Zfar - Znear);
	b.m[11] = -((Zfar + Znear) / (Zfar - Znear));

	b.m[12] = 0;
	b.m[13] = 0;
	b.m[14] = 0;
	b.m[15] = 1;

	this->multThis(b);

	return;

}

void glzMatrix::ortho2DPixelspace(int x, int y, glzOrigin origin)
{

	glzMatrix b;
	b.LoadIdentity();


	if (origin == glzOrigin::BOTTOM_LEFT)
	{
		b.ortho2D(-(x*0.5f), (x*0.5f), -(y*0.5f), (y*0.5f));
		b.translate(-(x*0.5f), -(y*0.5f), 0);
	}

	if (origin == glzOrigin::TOP_LEFT)
	{
		b.ortho2D((x*0.5f), -(x*0.5f), -(y*0.5f), (y*0.5f));
		b.translate(-(x*0.5f), (y*0.5f), 0);
	}

	this->multThis(b);

	return;

}

void glzMatrix::loadQuanternion(float q[4])
{
	glzMatrix b;

	b.m[0] = 1 - (2 * q[2] * q[2]) - (2 * q[3] * q[3]);
	b.m[1] = (2 * q[1] * q[2]) + (2 * q[0] * q[3]);
	b.m[2] = (2 * q[1] * q[3]) - (2 * q[0] * q[2]);
	b.m[3] = 0;

	b.m[4] = (2 * q[1] * q[2]) - (2 * q[0] * q[3]);
	b.m[5] = 1 - (2 * q[1] * q[1]) - (2 * q[3] * q[3]);
	b.m[6] = (2 * q[2] * q[3]) + (2 * q[0] * q[1]);
	b.m[7] = 0;

	b.m[8] = (2 * q[1] * q[3]) + (2 * q[0] * q[2]);
	b.m[9] = (2 * q[2] * q[3]) - (2 * q[0] * q[1]);
	b.m[10] = 1 - (2 * q[1] * q[1]) - (2 * q[2] * q[2]);
	b.m[11] = 0;

	b.m[12] = 0;
	b.m[13] = 0;
	b.m[14] = 0;
	b.m[15] = 1;

	this->multThis(b);
	return;
}


glzMatrix glzMatrix::operator*= (glzQuaternion b)
{
	glzMatrix a;

	a.m[0] = 1 - (2 * b.y * b.y) - (2 * b.z * b.z);
	a.m[1] = (2 * b.x * b.y) + (2 * b.w * b.z);
	a.m[2] = (2 * b.x * b.z) - (2 * b.w * b.y);
	a.m[3] = 0;

	a.m[4] = (2 * b.x * b.y) - (2 * b.w * b.z);
	a.m[5] = 1 - (2 * b.x * b.x) - (2 * b.z * b.z);
	a.m[6] = (2 * b.y * b.z) + (2 * b.w * b.x);
	a.m[7] = 0;

	a.m[8] = (2 * b.x * b.z) + (2 * b.w * b.y);
	a.m[9] = (2 * b.x * b.z) - (2 * b.w * b.x);
	a.m[10] = 1 - (2 * b.x * b.x) - (2 * b.y * b.y);
	a.m[11] = 0;

	a.m[12] = 0;
	a.m[13] = 0;
	a.m[14] = 0;
	a.m[15] = 1;

	this->multThis(a);
	return *this;
}


void glzQuaternion::multQuaternion(glzQuaternion b)
{
	glzQuaternion  nq;

	nq.w = -x * b.x - y * b.y - z * b.z + w * b.w;
	nq.x = x * b.w + y * b.z - z * b.y + w * b.x;
	nq.y = -x * b.z + y * b.w + z * b.x + w * b.y;
	nq.z = x * b.y - y * b.x + z * b.w + w * b.z;
	w = nq.w;
	x = nq.x;
	y = nq.y;
	z = nq.z;

	return;
}

void glzQuaternion::rotate(double a, double x, double y, double z)
{
	double angle = -a*PI_OVER_360;
	glzQuaternion q2;

	q2.w = cos(angle);
	q2.x = sin(angle)*x;
	q2.y = sin(angle)*y;
	q2.z = sin(angle)*z;

	this->normalize();
	multQuaternion(q2);

	return;
}
