
#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"


class Particle
{
public:
	Particle(Vector3 pos_, Vector3 vel_, float size_);
	~Particle();


	bool integrate(double t);

protected:
	physx::PxTransform pos;
	Vector3 vel;
	RenderItem* render;

	double size;

};

