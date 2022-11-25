#include "SpringForcegenerator.h"

SpringForceGenerator::SpringForceGenerator(double k, double resting_length, Particle* other) 
	: _k(k), _resting_length(resting_length), _other(other)
{
}

SpringForceGenerator::SpringForceGenerator(double k, double resting_length, Vector3 r2)
	: _k(k), _resting_length(resting_length)
{
	//creamos particula cubo en la posicion
	_other = new Particle(r2, 1, {1,1,1,1});
}

void SpringForceGenerator::updateForce(Particle* p, double t)
{

	Vector3 force = _other->getPos() - p->getPos();

	const float lenght = force.normalize();
	const float delta_x = lenght - _resting_length;

	force *= delta_x * _k;

	p->addForce(force);
}
