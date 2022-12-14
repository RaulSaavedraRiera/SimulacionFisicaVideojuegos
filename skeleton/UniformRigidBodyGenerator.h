#pragma once
#include <PxPhysics.h>
#include <PxScene.h>
#include <string>
#include "RenderUtils.hpp"
#include <list>
#include <random>

class WorldManager;

using namespace physx;
using namespace std;
class UniformRigidBodyGenerator
{
public:

	UniformRigidBodyGenerator(WorldManager* s, string name, Vector3 pos, Vector3 v, double iniSize, double rndV, double rndP, double rndS, PxPhysics* gP,double tBS, double n);
	~UniformRigidBodyGenerator() = default;

	list<PxRigidDynamic*> generateBodies(double t);

protected:

	const int maxN = 20;
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
};

