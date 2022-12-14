#include "HorizontalForceGenerator.h"

HorizontalForceGenerator::HorizontalForceGenerator(double k_, double t_, double positiveIni) : k(k_), time(t_), left(!positiveIni)
{
	currentTime = 0;
	lastChange = 0;
}

void HorizontalForceGenerator::updateForceRigids(physx::PxRigidDynamic* rigidBody, double t)
{
	if (!enable)
		return;

	currentTime += t;

	if (currentTime > time + lastChange)
	{
		lastChange = currentTime;
		left = !left;
	}

	if (time == lastChange)
		rigidBody->setLinearVelocity({ 0,0,0 });
		
	
	if (left)
		rigidBody->addForce(Vector3(-1, 0, 0) * k * rigidBody->getMass());
	else
		rigidBody->addForce(Vector3(1, 0, 0) * k * rigidBody->getMass());
	
}
