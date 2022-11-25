#pragma once
#include "ForceGenerator.h"
#include "core.hpp"

class SpringForceGenerator : public ForceGenerator
{
public:
	SpringForceGenerator(double k, double resting_length, Particle* other);
	SpringForceGenerator(double k, double resting_length, Vector3 r2);
	~SpringForceGenerator() = default;

	virtual void updateForce(Particle* p, double t);

	inline void setK(double k) { _k = k; }
	inline double getK() { return _k; }

protected:
	double _k;
	double _resting_length;
	Particle* _other;

};

