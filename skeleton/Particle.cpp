#include "Particle.h"
#include <math.h>
using namespace physx;

Particle::Particle(Vector3 pos_, Vector3 vel_, float size_, double tDestroy, Vector4 c, Vector3 acc_, float damping_, double m, bool i, bool colPlayer, bool forceSquareGeometry) : pos(pos_), vel(vel_), timeDestroy(tDestroy), size(size_), color(c), mass(m), implicit(i), colWithPlayer(colPlayer)
{
	acc = acc_;
	damping = damping_;
	timePass = 0;
	force = { 0,0,0 };

	inverseMass = 1 / mass;

	if (!forceSquareGeometry)
		render = new RenderItem(CreateShape(PxSphereGeometry(size)), &pos, color);
	else
		render = new RenderItem(CreateShape(PxBoxGeometry(size, size, size)), &pos, color);
}

Particle::Particle(Vector3 pos_, double size_, Vector4 color_, bool colP) : pos(pos_), size(size_), color(color_), colWithPlayer(colP)
{
	render = new RenderItem(CreateShape(PxBoxGeometry(size, size, size)), &pos, color);
}

Particle::Particle(Vector3 pos_, double sizeXZ, bool colP) : pos(pos_), size(sizeXZ), colWithPlayer(colP)
{
	render = new RenderItem(CreateShape(PxBoxGeometry(sizeXZ, 1, sizeXZ)), &pos, { 0,0,1,0 });
}

Particle::Particle(Vector3 pos_, Vector3 size_, Vector4 color_, bool colP) : pos(pos_), size(size_.x), colWithPlayer(colP)
{
	render = new RenderItem(CreateShape(PxBoxGeometry(size_.x, size_.y, size_.z)), &pos, color_);
}

Particle::~Particle()
{
	DeregisterRenderItem(render);
	delete render;
}

bool Particle::integrate(double t)
{
	timePass += t;

	//limitamos particula en y
	if (timePass > timeDestroy || pos.p.y < yMin || pos.p.y > yMax || pos.p.x < -limitX || pos.p.x > limitX)
		return false;

	if (inverseMass <= 0.0f)
		return true;

	if (implicit)
		pos.p += vel * t;

	Vector3 accTotal = { 0,0,0 }; accTotal = acc;
	accTotal += force * inverseMass;
	vel += accTotal * t;
	vel *= powf(damping, t);

	if (!implicit)
		pos.p += vel * t;

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
