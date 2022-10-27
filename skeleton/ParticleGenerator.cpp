
#include "SistemaDeParticulas.h"
#include "ParticleGenerator.h"
#include  <iostream>


ParticleGenerator::ParticleGenerator(SistemaDeParticulas* s, string name, Particle* p, int n, Vector3 pos, Vector3 vel, double rnd, double rndPos) :
	particleSystem(s), name(name), num_particles(n), random(rnd), randomPos(rndPos)
{
	setParticle(p);
	model->pos = physx::PxTransform(pos);
	model->vel = vel;


	lastGenerate = 0;
	currentTime = 0;
}

ParticleGenerator::~ParticleGenerator()
{
}




