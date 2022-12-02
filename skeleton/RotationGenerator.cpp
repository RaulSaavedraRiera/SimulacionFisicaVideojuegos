#include "RotationGenerator.h"

RotationGenerator::RotationGenerator(double k_, double R_, Vector3 p) : k(k_), R(R_), point(p)
{
}

void RotationGenerator::updateForceRigids(physx::PxRigidDynamic* rigidBody, double t)
{
	if (!enable)
		return;


	auto pos = rigidBody->getGlobalPose().p;

	auto difX = pos.x - point.x;
	auto difY = pos.y - point.y;
	auto difZ = pos.z - point.z;

	auto r2 = pow(difX, 2) + pow(difY, 2) + pow(difZ, 2);

	if (r2 > R*R)
		return;
	
	rigidBody->addTorque(Vector3(difX,difY, difZ) * k);
}
