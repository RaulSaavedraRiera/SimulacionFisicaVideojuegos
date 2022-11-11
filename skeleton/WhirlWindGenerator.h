#pragma once
#include "UniformWindGenerator.h";

class WhirlWindGenerator : public UniformWindGenerator
{
public:

	WhirlWindGenerator(float k, Vector3 point, int range, Vector3 air = {0,0,0});
	~WhirlWindGenerator();


	void updateForce(Particle* particle, double t) override;

protected:

};

