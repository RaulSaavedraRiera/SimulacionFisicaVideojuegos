#pragma once
#include "ParticleGenerator.h"
class GaussianParticleGenerator : public ParticleGenerator
{
public:

	GaussianParticleGenerator(SistemaDeParticulas* s, string name, Particle* p, int n, Vector3 pos, Vector3 v, Vector3 devTip_pos, Vector3 devTip_vel, double rnd, double rndPos);
	~GaussianParticleGenerator() = default;
	
	virtual list<Particle*> generateParticles(double t) override;

protected:

	normal_distribution<double>d; 
	normal_distribution<double>dP; 

	Vector3 devTip_pos, devTip_vel;

	double std_dev_t;
};

