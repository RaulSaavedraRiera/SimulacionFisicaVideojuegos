#pragma once
#include "ForceGenerator.h"
class FloatGenerator : public ForceGenerator
{
public:
	FloatGenerator(float h, float v, float d);
	FloatGenerator(Vector3 pos, Vector3 size, float v, float d);
	~FloatGenerator();

	virtual void updateForce(Particle* p, double t);
	virtual void updateForceRigids(physx::PxRigidDynamic* rigid, double duration);


protected:
	float _height;
	float _volume;
	float _liquid_density;
	float _gravity = 9.8;

	Particle* _liquid_particle;


	const float xSize = 30, zSize = 50, playerForce = 100;
};

