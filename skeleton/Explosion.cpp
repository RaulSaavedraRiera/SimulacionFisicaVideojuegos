#include "Explosion.h"
#include <cmath>
#include <iostream>

//hemos quitado se propague con el sonido
Explosion::Explosion(double k_, double R_, Vector3 p_) : k(k_), R(R_), point(p_) //R(R_)
{
	w = 0;
}

void Explosion::updateForce(Particle* particle, double t)
{
	if (!enable)
		return;

	if (fabs(particle->getInverseMass() < 1e-10))
		return;


	auto pos = particle->getPos();

	double r = sqrt(pow((pos.x - point.x), 2) + pow((pos.y - point.y), 2) + pow((pos.z - point.z), 2));

	Vector3 forceDir;

	if (r < R)
	{
		double mult = k / pow(r, 2);
		double elev = -(t / w);
		double mult2 = pow(e, elev);

		forceDir = Vector3(pos.x - point.x, pos.y - point.y, pos.z - point.z) * mult * mult2;
	}
	else
	{
		forceDir = { 0,0,0 };
	}

	Vector3 v = particle->getVel() - forceDir;
	float drag_coef = v.normalize();
	Vector3 dragF;
	drag_coef = (k * drag_coef) + k * drag_coef * drag_coef;
	dragF = -v * drag_coef;


	particle->addForce(dragF);



}

void Explosion::updateForceRigids(physx::PxRigidDynamic* rigid, double t)
{

	if (!enable)
		return;

	const double euler = std::exp(1.0);
	auto pos = rigid->getGlobalPose().p;
	auto difX = pos.x - point.x;
	auto difY = pos.y - point.y;
	auto difZ = pos.z - point.z;

	auto r2 = pow(difX, 2) + pow(difY, 2) + pow(difZ, 2);

	if (r2 > pow(R, 2))
	{
		return;
	}

	auto x = (k / r2) * difX * pow(euler, (-t / w));
	auto y = (k / r2) * difY * pow(euler, (-t / w));
	auto z = (k / r2) * difZ * pow(euler, (-t / w));

	Vector3 force(x, y, z);


	rigid->addForce(force);
}

void Explosion::updateValues(double t)
{
	if (!enable)
		return;

	w += t;

	//añadido para area explosion afecta el tiempo
	//R += t * velSonido;

}
