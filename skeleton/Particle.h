
#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"


class Particle
{
public:
	Particle(Vector3 pos_, Vector3 vel_, float size_, Vector3 acc_ = { 0, -2 , 0 }, float damping_ = 0.999 );
	~Particle();


	bool integrate(double t);

protected:
	physx::PxTransform pos;
	Vector3 vel;
	RenderItem* render;

	Vector3 acc;
	float damping;

};

