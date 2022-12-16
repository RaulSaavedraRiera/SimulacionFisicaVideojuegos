#include "RotationGenerator.h"

RotationGenerator::RotationGenerator(double k_, double R_, Vector3 p) : k(k_), R(R_), point(p)
{
}

void RotationGenerator::updateForceRigids(physx::PxRigidDynamic* rigidBody, double t)
{
	if (!enabled)
		return;


	auto pos = rigidBody->getGlobalPose().p;

	auto difX = pos.x - point.x;
	auto difY = pos.y - point.y;
	auto difZ = pos.z - point.z;

	auto r2 = pow(difX, 2) + pow(difY, 2) + pow(difZ, 2);

	if (r2 > R*R)
		return;
	
	//puedes añadirle otro vector que mire para el centro y asi nucna se alejen si no que se vayan dando la vuelta
	rigidBody->addTorque(Vector3(difX,difY, difZ) * k);
}
