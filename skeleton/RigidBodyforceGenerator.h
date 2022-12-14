#pragma once
#include <list>
#include <PxPhysics.h>
#include <PxScene.h>
#include <string>
#include "RenderUtils.hpp"
#include <random>

using namespace physx;
using namespace std;


class ForceGenerator;

class RigidBodyforceGenerator {
public:

	RigidBodyforceGenerator() = default;
	~RigidBodyforceGenerator() = default;


	virtual std::list<PxRigidDynamic*> generateBodies(double t) = 0;
	virtual std::list<ForceGenerator*> getForces() = 0;
};
