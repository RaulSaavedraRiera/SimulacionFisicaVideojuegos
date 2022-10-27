#pragma once
#include "Proyectile.h"
class CanonBall : public Proyectile
{
public:
	CanonBall(Vector3 pos_, float vel_, float size_, double t_, Vector3 acc_, float damping_, float mass_);
	~CanonBall() = default;

	Particle* clone() const override;
};

