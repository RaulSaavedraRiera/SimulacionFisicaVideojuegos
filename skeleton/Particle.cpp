#include "Particle.h"
#include <math.h>
using namespace physx;

Particle::Particle(Vector3 pos_, Vector3 vel_, float size_, Vector3 acc_, float damping_): pos(pos_), vel(vel_)
{
	acc = acc_;
	damping = damping_;

	render = new RenderItem(CreateShape(PxSphereGeometry(size_)), &pos, {1, 0, 0, 1});
}

Particle::~Particle()
{
	delete render;
}

bool Particle::integrate(double t)
{
	pos.p += vel * t;
	vel = (vel * pow(damping, t)) + (acc * t);


	render->color = { (float)(rand() % 10) / 10, 0 , 0 , 1 };

	return true;
}
