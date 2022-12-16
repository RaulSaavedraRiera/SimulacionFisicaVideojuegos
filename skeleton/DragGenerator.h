#pragma once
#include "ForceGenerator.h"
#include "core.hpp"
#include <iostream>

class DragGenerator : public ForceGenerator
{
public:
	DragGenerator();
	DragGenerator(const float k1, const float k2);
	~DragGenerator() = default;

	virtual void updateForce(Particle* particle, double t);

	inline void setDrag(float k1, float k2) { _k1 = k1; _k2 = k2; };

	inline float getK1() { return (_k1); };
	inline float getK2() { return (_k2); };

	void changeEnable() { enabled = !enabled; };

protected:
	Vector3 _wind;

	float _k1;
	float _k2;

};

