#pragma once
#include "Particle.h"
#include <list>
#include <memory>

class CircleParticleGenerator;
class FireWork : public Particle
{

public:

	FireWork(Vector3 pos_, Vector3 vel_, float size_, double tDestroy, std::list<std::shared_ptr<ParticleGenerator>> g, Vector4 color = { 1, 1, 1, 1 }, Vector3 acc_ = { 0, -2 , 0 }, float damping_ = 0.999);
	~FireWork() = default;

	std::list<Particle*> explode();
	virtual Particle* clone() const { return new FireWork(pos.p, vel, size, timeDestroy, _gens, color, acc, damping); };


protected:
	std::list<std::shared_ptr<ParticleGenerator>> _gens;

};

