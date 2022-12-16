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

bool PlayerController::CollisionWithParticle(Vector3 posParticle, float sizeP, bool sphere)
{
	if (abs(posParticle.x - player->getGlobalPose().p.x) > sizeP + size || abs(posParticle.y - player->getGlobalPose().p.y) > sizeP + size || abs(posParticle.z - player->getGlobalPose().p.z) > sizeP + size)
		return false;

	if (sphere) {
		float dx = posParticle.x - player->getGlobalPose().p.x;
		float dy = posParticle.y - player->getGlobalPose().p.y;
		float dz = posParticle.z - player->getGlobalPose().p.z;
		float distance = sqrt(dx * dx + dy * dy + dz * dz);

		return distance < (size + sizeP);
	}
	else
	{
		float dx = fabs(player->getGlobalPose().p.x - posParticle.x);
		float dy = fabs(player->getGlobalPose().p.y - posParticle.y);
		float dz = fabs(player->getGlobalPose().p.z - posParticle.z);
		float distance = sqrt(dx * dx + dy * dy + dz * dz);

		return distance < size + sizeP;
	}

}

void PlayerController::resetPosition()
{
	player->setGlobalPose(PxTransform(iniPos));
	player->setLinearVelocity({ 0,0,0 });
	player->setAngularVelocity({ 0, 0, 0 });
}
