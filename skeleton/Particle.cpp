#include "Particle.h"
#include <math.h>
using namespace physx;

Particle::Particle(Vector3 pos_, Vector3 vel_, float size_, double tDestroy, Vector4 c, Vector3 acc_, float damping_): pos(pos_), vel(vel_), timeDestroy(tDestroy), size(size_), color(c)
{
	acc = acc_;
	damping = damping_;
	timePass = 0;

	render = new RenderItem(CreateShape(PxSphereGeometry(size)), &pos, color);
}

Particle::~Particle()
{
	DeregisterRenderItem(render);
	delete render;
}

bool Particle::integrate(double t)
{
	timePass += t;

	if (timePass > timeDestroy)
		return false;

	pos.p += vel * t;
	vel = (vel * pow(damping, t)) + (acc * t);


	//render->color = { (float)(rand() % 10) / 10, 0 , 0 , 1 };

	return true;
}
