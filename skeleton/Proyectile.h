#pragma once
#include "Particle.h"
class Proyectile : public Particle
{
public:

	Proyectile(Vector3 pos_, float vel_, float size_, double t, Vector3 acc_, float damping_, float mass);
	~Proyectile() = default;

	bool integrate(double t) override;

	
protected:

	float mass;
};

