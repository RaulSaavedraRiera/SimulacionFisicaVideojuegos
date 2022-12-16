#pragma once
#include <PxPhysics.h>
#include <PxScene.h>
#include <list>
#include "RenderUtils.hpp"
#include "RigidBodyForceRegistry.h"
#include "Explosion.h"
#include "RotationGenerator.h"
#include "HorizontalForceGenerator.h"
#include "UniformRigidBodyGenerator.h"
#include "StaticRigidBodyGenerator.h"

#include "SistemaDeParticulas.h"

using namespace physx;

class PlayerController;
class UniformRigidBodygenerator;

class WorldManager
{
public:

	WorldManager(PxPhysics* gPhyscis, PxScene* gScene, SistemaDeParticulas* particleContr);
	~WorldManager();


	void InputActions(char c);
	void generateStaticRoom();
	void generateDynamicCube();
	void update(double t);
	void generateRigids(std::list<PxRigidDynamic*> d, std::list<ForceGenerator*> generatorsAttached);

	PxRigidDynamic* instanciatePlayer(PlayerController* controller, Vector3 p, float size_);

	void generateLevel();
	
	void generateZone1();
	void generateRotationZone(Vector3 pos);
	void generateHorizontalWallsZone(Vector3 pos);
	void generateCanonZone(Vector3 pos);
	void generateDragZone(Vector3 pos);
	void generateWaterZone(Vector3 pos);
	void generateBouncyZone(Vector3 pos);



	void generateFloor(Vector3 pos);



protected:
	RigidBodyForceRegistry* forceRegistry;
	list<RenderItem*> renders;

	PxPhysics* gPhyscis;
	PxScene* gScene;

	Vector3 iniPos = { 0,7.5,0 };
	Vector3 iniVel = { 0,0,0 };
	Vector3 iniSize = { 1,1,1 };

	std::list<RigidBodyforceGenerator*> generators;
	std::list<PxRigidDynamic*> rigids;
	/*Explosion* explosion;
	RotationGenerator* rotation;*/

	PxRigidDynamic* player;
	PlayerController* controller;
	SistemaDeParticulas* particleController;

	const float minY = -10;
	const float sizeZoneZ = 50, sizeZoneX = 30;
	float winZ;

	bool win = false;

};

