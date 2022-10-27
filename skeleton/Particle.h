
#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"


class Particle
{
	friend class ParticleGenerator;
	friend class GaussianParticleGenerator;
	friend class UniformParticleGenerator;

public:
	Particle(Vector3 pos_, Vector3 vel_, float size_, double tDestroy, Vector4 color = { 1, 1, 1, 1 }, Vector3 acc_ = { 0, -2 , 0 }, float damping_ = 0.999);
	~Particle();


	virtual bool integrate(double t);

	virtual Particle* clone() const { return new Particle(pos.p, vel, size, timeDestroy, color, acc, damping); };

protected:
	physx::PxTransform pos;
	Vector3 vel;
	Vector4 color;

	RenderItem* render;

	Vector3 acc;
	float damping;
	double timeDestroy, timePass;

	double size;
};

