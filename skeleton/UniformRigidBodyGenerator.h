#pragma once

#include "RigidBodyforceGenerator.h"

class WorldManager;
class ForceGenerator;

class UniformRigidBodyGenerator : public RigidBodyforceGenerator
{
public:
	//hay que limpiar la lista de generadores de alguna manera
	UniformRigidBodyGenerator(WorldManager* s, list<ForceGenerator*> forcesAttach, string name, Vector3 pos, Vector3 v, double iniSize, double rndV, double rndP, double rndS, PxPhysics* gP, double tBS, double n);
	~UniformRigidBodyGenerator() = default;

	list<PxRigidDynamic*> generateBodies(double t) override;
	list<ForceGenerator*> getForces() override { return forces; };

protected:

	const int maxN = 10;
	int currentN = 0;
	string name;

	Vector3 pos, vel;
	double iniSize;

	uniform_real_distribution<double>d;
	uniform_real_distribution<double>dP;

	double randomSize, randomPos, randomVel;
	double std_dev_t;
	double currentTime, timeBtwSpawn, lastSpawn, nSpawn;

	WorldManager* worldManager;
	PxPhysics* gPhyscis;
	PxScene* gScene;

	list<ForceGenerator*> forces;
};