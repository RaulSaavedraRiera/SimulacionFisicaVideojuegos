#pragma once
#include <PxPhysics.h>
#include <PxScene.h>
#include <list>
#include "RenderUtils.hpp"
#include "RigidBodyForceRegistry.h"
#include "Explosion.h"
#include "RotationGenerator.h"


using namespace physx;

class PlayerController;

class WorldManager
{
public:

	WorldManager(PxPhysics* gPhyscis, PxScene* gScene);
	~WorldManager();


	void InputActions(char c);
	void generateStaticRoom();
	void generateDynamicCube();
	void update(double t);

	PxRigidDynamic* instanciatePlayer(PlayerController* controller, Vector3 p, float size_);


	void generateZone1();
	void generateRotationZone(Vector3 pos);


protected:
	RigidBodyForceRegistry* forceRegistry;

	PxPhysics* gPhyscis;
	PxScene* gScene;

	Vector3 iniPos = { 0,7.5,0 };
	Vector3 iniVel = { 0,0,0 };
	Vector3 iniSize = { 1,1,1 };

	std::list<ForceGenerator*> generators;
	std::list<PxRigidDynamic*> rigids;
	/*Explosion* explosion;
	RotationGenerator* rotation;*/

	PxRigidDynamic* player;
	PlayerController* controller;

	const float minY = -10;
	const float sizeZoneZ = 15, sizeZoneX = 30;

};

