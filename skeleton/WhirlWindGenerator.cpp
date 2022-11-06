#include "WhirlWindGenerator.h"

WhirlWindGenerator::WhirlWindGenerator(float k, Vector3 point, Vector3 air, int range) : UniformWindGenerator(k ,k, point, air, range)
{
}

WhirlWindGenerator::~WhirlWindGenerator()
{
}

void WhirlWindGenerator::updateForce(Particle* particle, double t)
{
	if (fabs(particle->getInverseMass() < 1e-10) || outZone(particle->getPos()))
		return;

	auto p = particle->getPos();

	Vector3 airDir = Vector3(
		-(p.z - point.z),
		50 - (p.y - point.y),
		p.x - point.x
	);

	Vector3 v = particle->getVel() + airDir;
	float drag_coef = v.normalize();
	Vector3 dragF;
	drag_coef = (_k1 * drag_coef) + _k2 * drag_coef * drag_coef;
	dragF = -v * drag_coef;


	particle->addForce(dragF);
}
