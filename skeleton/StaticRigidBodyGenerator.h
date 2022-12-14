#pragma once
#include "RigidBodyforceGenerator.h"

class WorldManager;
class ForceGenerator;
class StaticRigidBodyGenerator : public RigidBodyforceGenerator
{
public:
	//hay que limpiar la lista de generadores de alguna manera
	StaticRigidBodyGenerator(WorldManager* s, list<ForceGenerator*> forcesAttach, string name, Vector3 pos, double iniSize,double rndS, PxPhysics* gP, double tBS);
	~StaticRigidBodyGenerator() = default;

	list<PxRigidDynamic*> generateBodies(double t) override;
	list<ForceGenerator*> getForces() override { return forces; };

protected:

	const int maxN = 3;
	int currentN = 0;
	string name;

	Vector3 pos;
	double iniSize;

	
	double randomSize;

	double currentTime, timeBtwSpawn, lastSpawn;

	WorldManager* worldManager;
	PxPhysics* gPhyscis;
	PxScene* gScene;

	list<ForceGenerator*> forces;
};