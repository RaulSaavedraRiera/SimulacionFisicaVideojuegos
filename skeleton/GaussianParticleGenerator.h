#pragma once
#include "ParticleGenerator.h"
#include "ForceGenerator.h"
#include "ParticleForceRegistry.h"

class GaussianParticleGenerator : public ParticleGenerator
{
public:

	GaussianParticleGenerator(SistemaDeParticulas* s, string name, Particle* p, int n, Vector3 pos, Vector3 v, Vector3 devTip_pos, Vector3 devTip_vel, double rnd, double rndPos, double timeGenerate, ParticleForceRegistry* registry = nullptr, std::list<ForceGenerator*> f = std::list<ForceGenerator*>());
	~GaussianParticleGenerator() = default;
	
	virtual list<Particle*> generateParticles(double t) override;

	void setXRandomPosMod(double newV) { xRandomMod = newV; };
	void setYRandomPosMod(double newV) { yRandomMod = newV; };
	void setZRandomPosMod(double newV) { zRandomMod = newV; };

	void GenerationsCanCollideWithPlayer() { model->setCanColPlayer(true); }

protected:

	normal_distribution<double>d; 
	normal_distribution<double>dP; 

	Vector3 devTip_pos, devTip_vel;
	
	std::list<ForceGenerator*> forces;
	ParticleForceRegistry* registry;

	double std_dev_t;

	double xRandomMod, yRandomMod, zRandomMod;
};

