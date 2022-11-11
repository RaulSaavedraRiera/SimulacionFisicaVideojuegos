#include "Particle.h"
#include <math.h>
using namespace physx;

Particle::Particle(Vector3 pos_, Vector3 vel_, float size_, double tDestroy, Vector4 c, Vector3 acc_, float damping_, double m) : pos(pos_), vel(vel_), timeDestroy(tDestroy), size(size_), color(c), mass(m)
{
	acc = acc_;
	damping = damping_;
	timePass = 0;
	force = { 0,0,0 };

	inverseMass = 1 / mass;

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

	if (inverseMass <= 0.0f)
		return true;

	pos.p += vel * t;
	Vector3 accTotal = { 0,0,0 }; accTotal = acc;
	accTotal += force * inverseMass;
	vel += accTotal * t;
	vel *= powf(damping, t);

	clearForce();

	/*pos.p += vel * t;
	vel = (vel * pow(damping, t)) + (acc * t);*/


	//render->color = { (float)(rand() % 10) / 10, 0 , 0 , 1 };

	return true;
}

void Particle::changePos(float x, float y, float z)
{
	pos.p += {x, y, z};
}
