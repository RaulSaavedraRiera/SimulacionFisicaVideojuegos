#pragma once
#include "ForceGenerator.h"
#include <PxPhysics.h>
#include "WorldManager.h"

using namespace physx;
class PlayerController : public ForceGenerator
{
public:
	PlayerController(float k, WorldManager* manager);
	~PlayerController();
	void addForce(char c);
	void change() { enable = !enable; };
	PxRigidDynamic* getPlayer() { return player; };
	Vector3 getPlayerPos() { return player->getGlobalPose().p; };


	virtual void updateForce(Particle* particle, double t) {};
	virtual void updateForceRigids(physx::PxRigidDynamic* particle, double t) {};

protected:

	PxRigidDynamic* player;
	const Vector3 iniPos = { 0, 10, 0 };
	const float size = 2;

	bool enable = false;
	double k;
};

