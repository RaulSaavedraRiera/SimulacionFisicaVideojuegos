#pragma once
#include "UniformWindGenerator.h";

class WhirlWindGenerator : public UniformWindGenerator
{
public:

	WhirlWindGenerator(float k, Vector3 point, Vector3 air, int range);
	~WhirlWindGenerator();


	void updateForce(Particle* particle, double t) override;

protected:

};

