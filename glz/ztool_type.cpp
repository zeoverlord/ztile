
using namespace std;

#include "ztool-type.h"
#include "ztool-glz.h"
#include "ztool-geo.h"


//glzspeed glzlength::operator/ (glzsecond b) { glzspeed sp(L / b.get()); return sp; }



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

/**/
void glzMatrix::LoadIdentity(void)
{
m[0] = 1;
m[1] = 0;
m[2] = 0;
m[3] = 0;

m[4] = 0;
m[5] = 1;
m[6] = 0;
m[7] = 0;

m[8] = 0;
m[9] = 0;
m[10] = 1;
m[11] = 0;

m[12] = 0;
m[13] = 0;
m[14] = 0;
m[15] = 1;
return;
}

glzMatrix glzMatrix::operator*= (glzMatrix b)
{
	glzMatrix  nm,a(m); // should be done with doubles some day
	int v[] = { 0, 1, 2, 3};

	for (auto i : v){  //Cycle through each vector of first matrix.
		m[i * 4 + 0] = a.m[i * 4] * b.m[0] + a.m[i * 4 + 1] * b.m[4] + a.m[i * 4 + 2] * b.m[8] + a.m[i * 4 + 3] * b.m[12];
		m[i * 4 + 1] = a.m[i * 4] * b.m[1] + a.m[i * 4 + 1] * b.m[5] + a.m[i * 4 + 2] * b.m[9] + a.m[i * 4 + 3] * b.m[13];
		m[i * 4 + 2] = a.m[i * 4] * b.m[2] + a.m[i * 4 + 1] * b.m[6] + a.m[i * 4 + 2] * b.m[10] + a.m[i * 4 + 3] * b.m[14];
		m[i * 4 + 3] = a.m[i * 4] * b.m[3] + a.m[i * 4 + 1] * b.m[7] + a.m[i * 4 + 2] * b.m[11] + a.m[i * 4 + 3] * b.m[15];
	}


	return glzMatrix(m);
}


void glzMatrix::rotate(double a, double x, double y, double z)
{

	double angle = a*PI_OVER_180;
	glzMatrix m2;

	m2.m[0] = 1 + (1 - cos(angle))*(x*x - 1);
	m2.m[1] = -z*sin(angle) + (1 - cos(angle))*x*y;
	m2.m[2] = y*sin(angle) + (1 - cos(angle))*x*z;
	m2.m[3] = 0;

	m2.m[4] = z*sin(angle) + (1 - cos(angle))*x*y;
	m2.m[5] = 1 + (1 - cos(angle))*(y*y - 1);
	m2.m[6] = -x*sin(angle) + (1 - cos(angle))*y*z;
	m2.m[7] = 0;

	m2.m[8] = -y*sin(angle) + (1 - cos(angle))*x*z;
	m2.m[9] = x*sin(angle) + (1 - cos(angle))*y*z;
	m2.m[10] = 1 + (1 - cos(angle))*(z*z - 1);
	m2.m[11] = 0;

	m2.m[12] = 0;
	m2.m[13] = 0;
	m2.m[14] = 0;
	m2.m[15] = 1;

	multThis(m2);

	return;
}