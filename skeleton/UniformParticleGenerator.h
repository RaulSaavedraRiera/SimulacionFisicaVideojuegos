#pragma once
#include "ParticleGenerator.h"
class UniformParticleGenerator : public ParticleGenerator
{
public:

	UniformParticleGenerator(SistemaDeParticulas* s, string name, Particle* p, int n, Vector3 pos, Vector3 v, Vector3 wPos, Vector3 wVel, double rnd, double rndP);
	~UniformParticleGenerator() = default;

	list<Particle*> generateParticles(double t) override;

	void ChangePos(Vector3 newP) { model->setPos(newP); };

protected:

	Vector3 vel_width, pos_width;


	uniform_real_distribution<double>d;
	uniform_real_distribution<double>dP;
	
	double std_dev_t;

	
};

