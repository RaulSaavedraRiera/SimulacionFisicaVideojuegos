#include "PlayerController.h"

PlayerController::PlayerController(float k_, WorldManager* manager) : k(k_)
{
	player = manager->instanciatePlayer(this, iniPos, size);
}

PlayerController::~PlayerController()
{
	player = nullptr;
}

void PlayerController::addForce(char c)
{
	Vector3 v = { 0,0,0 };

	switch (c)
	{
	case 'a':
		v -= {0, 0, 1};
		break;
	case 'd':
		v += {0, 0, 1};
		break;
	case 'w':
		v += {1, 0, 0};
		break;
	case 's':
		v -= {1, 0, 0};
		break;
	}
	player->addTorque(v * k * 2000);
}

bool PlayerController::CollisionWithParticle(Vector3 posParticle, Vector3 areaParticle)
{
	if (abs(posParticle.x - player->getGlobalPose().p.x) > 5 || abs(posParticle.y - player->getGlobalPose().p.y) > 5 || abs(posParticle.z - player->getGlobalPose().p.z) > 5)
		return false;

	if (abs(player->getGlobalPose().p.x - posParticle.x) < areaParticle.x / 2 + size / 2 && abs(player->getGlobalPose().p.y - posParticle.y) < areaParticle.y / 2 + size / 2 &&
		abs(player->getGlobalPose().p.z - posParticle.z) < areaParticle.z / 2 + size / 2)
		return true;

}

void PlayerController::resetPosition()
{
	player->setGlobalPose(PxTransform(iniPos));
	player->setLinearVelocity({ 0,0,0 });
	player->setAngularVelocity({ 0, 0, 0 });
}
