#include "SpringForcegenerator.h"

SpringForceGenerator::SpringForceGenerator(double k, double resting_length, Particle* other, double d) 
	: _k(k), _resting_length(resting_length), _other(other), _minL(d)
{
}

SpringForceGenerator::SpringForceGenerator(double k, double resting_length, Vector3 r2, double d)
	: _k(k), _resting_length(resting_length), _minL(d)
{
	//creamos particula cubo en la posicion
	_other = new Particle(r2, 1, {1,1,1,1});
}

void SpringForceGenerator::updateForce(Particle* p, double t)
{

	Vector3 force = _other->getPos() - p->getPos();

	
	const float lenght = force.normalize();

	//if (lenght < _minL) {
	//	p->setVel({ 0,0,0 });
	//	return;
	//}

	const float delta_x = lenght - _resting_length;

	force *= delta_x * _k;

	p->addForce(force);
}
