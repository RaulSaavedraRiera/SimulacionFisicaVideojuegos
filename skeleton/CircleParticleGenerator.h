#pragma once
#include "GaussianParticleGenerator.h"
class CircleParticleGenerator : public GaussianParticleGenerator
{
public:
	CircleParticleGenerator(SistemaDeParticulas* s, string name, Particle* p, int n, Vector3 pos, Vector3 v, double rndV = 5., double rndPos = 0.1);
	~CircleParticleGenerator() = default;

};

