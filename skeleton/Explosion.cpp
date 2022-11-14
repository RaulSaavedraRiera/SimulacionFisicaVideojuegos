#include "Explosion.h"
#include <cmath>

Explosion::Explosion(double k_, double R_, Vector3 p_) : k(k_), R(0), point(p_) //R(R_)
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

void Explosion::updateValues(double t)
{
	if (!enable)
		return;

	w += t;

	//añadido para area explosion afecta el tiempo
	R += t * velSonido; 

}
