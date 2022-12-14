#pragma once
#include <PxPhysics.h>
#include <PxScene.h>
#include "RenderUtils.hpp"
#include "RigidBodyForceRegistry.h"
#include "Explosion.h"
#include "RotationGenerator.h"
#include "UniformRigidBodyGenerator.h"

using namespace physx;

class WorldManager
{
public:

	WorldManager(PxPhysics* gPhyscis, PxScene* gScene);
	~WorldManager();


	void InputActions(char c);
	void generateStaticRoom();
	void generateDynamicCube();
	void generateCubes(std::list<PxRigidDynamic*> d);
	void update(double t);


protected:
	RigidBodyForceRegistry* forceRegistry;

	PxPhysics* gPhyscis;
	PxScene* gScene;

	Vector3 iniPos = { 0,7.5,0 };
	Vector3 iniVel = { 0,0,0 };
	Vector3 iniSize = { 1,1,1 };

	Explosion* explosion;
	RotationGenerator* rotation;

	UniformRigidBodyGenerator* uniformRigidBodyGenerator;
};

