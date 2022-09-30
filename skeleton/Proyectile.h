#pragma once
#include "Particle.h"
class Proyectile : public Particle
{
public:

	Proyectile(Vector3 pos_, float vel_, float size_, Vector3 acc_, float damping_, float mass_);
	~Proyectile() = default;

	bool integrate(double t) override;

protected:

	float mass;
};

