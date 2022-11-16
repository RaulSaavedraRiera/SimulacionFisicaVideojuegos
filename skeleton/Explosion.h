#pragma once
#include "ForceGenerator.h"
class Explosion :  public ForceGenerator
{
 public:
	Explosion(double k, double R, Vector3 p);
	~Explosion() = default;

	virtual void updateForce(Particle* particle, double t);

	void updateValues(double t);

	void change() { enable = !enable; };

protected:

	bool enable = false;

	double k, R, w;
	Vector3 point;


	const double e = 2.71828182846, velSonido = 343;
};

