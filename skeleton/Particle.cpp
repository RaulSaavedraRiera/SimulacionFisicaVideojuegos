#include "Particle.h"
#include <math.h>
using namespace physx;

Particle::Particle(Vector3 pos_, Vector3 vel_, float size_) : pos(pos_), vel(vel_), size(size_)
{
	render = new RenderItem(CreateShape(PxSphereGeometry(size_)), &pos, {1, 0, 0, 1});
}

Particle::~Particle()
{
	delete render;
}

bool Particle::integrate(double t)
{
	pos.p += vel * t;

	render->color = { (float)(rand() % 10) / 10, 0 , 0 , 1 };

	return true;
}
