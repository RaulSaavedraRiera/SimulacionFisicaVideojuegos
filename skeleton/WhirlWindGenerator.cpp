#include "WhirlWindGenerator.h"

WhirlWindGenerator::WhirlWindGenerator(float k, Vector3 point, int range, Vector3 air) : UniformWindGenerator(k ,k, point, air, range)
{
}

WhirlWindGenerator::~WhirlWindGenerator()
{
}

//k1 funciona como k
void WhirlWindGenerator::updateForce(Particle* particle, double t)
{
	if (!enabled) return;

	if (fabs(particle->getInverseMass() < 1e-10) || outZone(particle->getPos()))
		return;

	auto p = particle->getPos();

	Vector3 airDir =  _k1 * Vector3(
		-(p.z - point.z) - 0.1*(p.x - point.x),
		20 - (p.y - point.y),
		(p.x - point.x) - 0.1*(p.z - point.z)
	);

	Vector3 v = particle->getVel() - airDir;
	float drag_coef = v.normalize();
	Vector3 dragF;
	drag_coef = (_k1 * drag_coef) + _k1 * drag_coef * drag_coef;
	dragF = -v * drag_coef;


	particle->addForce(dragF);
}
