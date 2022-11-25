#pragma once
#include "ForceGenerator.h"
class FloatGenerator : public ForceGenerator
{
public:
	FloatGenerator(float h, float v, float d);
	~FloatGenerator();

	virtual void updateForce(Particle* p, double t);


protected:
	float _height;
	float _volume;
	float _liquid_density;
	float _gravity = 9.8;

	Particle* _liquid_particle;
};

