#include "PlayerController.h"

PlayerController::PlayerController(float k_, WorldManager* manager) : k(k_)
{
	player = manager->instanciatePlayer(iniPos, size);
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
	player->addTorque(v * k*2000);
}
