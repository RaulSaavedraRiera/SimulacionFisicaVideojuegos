#include "CanonBall.h"


CanonBall::CanonBall(Vector3 pos_, float vel_, float size_, double t_, Vector3 acc_, float damping_, float mass_) 
	: Proyectile(pos_,vel_, size_, t_, acc_, damping_, mass_)
{	
	vel = (GetCamera()->getDir()) * vel_ + Vector3(0, vel_, 0);
}

Particle* CanonBall::clone() const
{
	return new CanonBall(*this);
}
