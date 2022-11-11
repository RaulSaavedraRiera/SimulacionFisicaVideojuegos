#include "UniformWindGenerator.h"

UniformWindGenerator::UniformWindGenerator(float k1, float k2, Vector3 point, Vector3 air, int range) : DragGenerator(k1, k2)
{
	_k1 = k1;
	_k2 = k2;
	this->point = point;
	this->air = air;

	xMax = point.x + range;
	xMin = point.x - range;
	yMax = point.y + range;
	yMin = point.y - range;
	zMax = point.z + range;
	zMin = point.z - range;

}
UniformWindGenerator::~UniformWindGenerator()
{
}

void UniformWindGenerator::updateForce(Particle* particle, double t)
{
	if (fabs(particle->getInverseMass() < 1e-10) || outZone(particle->getPos()))
		return;

	auto p = particle->getPos();

	Vector3 v = particle->getVel() - air;
	float drag_coef = v.normalize();
	Vector3 dragF;
	drag_coef = (_k1 * drag_coef) + _k2 * drag_coef * drag_coef;
	dragF = -v * drag_coef;


	particle->addForce(dragF);

}

bool UniformWindGenerator::outZone(Vector3 pP)
{
	return pP.x < xMin || pP.x > xMax || pP.y < yMin || pP.y > yMax || pP.z < zMin || pP.z > zMax;
}
