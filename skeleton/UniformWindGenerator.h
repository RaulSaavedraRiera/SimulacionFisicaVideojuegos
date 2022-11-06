#pragma once
#include "DragGenerator.h"
class UniformWindGenerator : public DragGenerator
{
public:
	UniformWindGenerator(float k1, float k2, Vector3 point, Vector3 air, int range);
	~UniformWindGenerator();

	void updateForce(Particle* particle, double t) override;


	bool outZone(Vector3 pP);

protected:

	Vector3 point, air;

	int xMax;
	int xMin;
	int yMax;
	int yMin;
	int zMax;
	int zMin;
};

