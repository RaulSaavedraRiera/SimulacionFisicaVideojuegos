#include "Proyectile.h"

Proyectile::Proyectile(Vector3 pos_, float vel_, float size_, Vector3 acc_, float damping_, float mass_) : Particle(pos_, {0,0,0}, size_, acc_, damping_)
{
	mass = mass_;
}


bool Proyectile::integrate(double t)
{
	pos.p += vel * t;
	vel = (vel * pow(damping, t)) + (acc * mass * t);

	return true;
}
