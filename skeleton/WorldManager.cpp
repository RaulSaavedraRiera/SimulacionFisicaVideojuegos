#include "WorldManager.h"
#include <random>


WorldManager::WorldManager(PxPhysics* p, PxScene* s) : gPhyscis(p), gScene(s)
{
	forceRegistry = new RigidBodyForceRegistry();
	explosion = new Explosion(500, 40, { 0, -1, 0 });
	rotation = new RotationGenerator(10, 100, { 0,0,0 });
}

WorldManager::~WorldManager()
{
}

void WorldManager::InputActions(char c)
{
	switch (c)
	{
	case 'j':
		generateStaticRoom();
		break;
	case 'k':
		generateDynamicCube();
		break;
	case 'l':
		explosion->change();
		break;
	case 'm':
		rotation->change();
		break;
	default:
		break;
	}
}

void WorldManager::generateStaticRoom()
{
	//Plane as a solid rigid
	PxRigidStatic* Suelo = gPhyscis->createRigidStatic(PxTransform({ 0, 0, 0 }));
	PxShape* shape = CreateShape(PxBoxGeometry(20, 1, 20));
	Suelo->attachShape(*shape);
	new RenderItem(shape, Suelo, {0.8, 0.8, 0.8, 1});
	gScene->addActor(*Suelo);
	// Add wall

	/*PxRigidStatic* ParedB; PxShape* shape_pared;

	ParedB = gPhyscis->createRigidStatic(PxTransform({ 0, 10, 19.5 }));
	shape_pared = CreateShape(PxBoxGeometry(20, 10, 1));
	ParedB->attachShape(*shape_pared);
	new RenderItem(shape_pared, ParedB, { 0.8, 0.8, 0.8, 1 });
	gScene->addActor(*ParedB);

	ParedB = gPhyscis->createRigidStatic(PxTransform({ 0, 10, -19.5 }));
	shape_pared = CreateShape(PxBoxGeometry(20, 10, 1));
	ParedB->attachShape(*shape_pared);
	new RenderItem(shape_pared, ParedB, { 0.8, 0.8, 0.8, 1 });
	gScene->addActor(*ParedB);

	ParedB = gPhyscis->createRigidStatic(PxTransform({ -19.5, 10, 0 }));
	shape_pared = CreateShape(PxBoxGeometry(1, 10, 20));
	ParedB->attachShape(*shape_pared);
	new RenderItem(shape_pared, ParedB, { 0.8, 0.8, 0.8, 1 });
	gScene->addActor(*ParedB);

	ParedB = gPhyscis->createRigidStatic(PxTransform({ 19.5, 10, 0 }));
	shape_pared = CreateShape(PxBoxGeometry(1, 10, 20));
	ParedB->attachShape(*shape_pared);
	new RenderItem(shape_pared, ParedB, { 0.8, 0.8, 0.8, 1 });
	gScene->addActor(*ParedB);*/

}

void WorldManager::generateDynamicCube()
{
	std::default_random_engine rnd{ std::random_device{}() };
	std::uniform_real_distribution<double> pos(-15, 15);
	std::uniform_real_distribution<double> s(-0.5, 0.5);
	std::uniform_real_distribution<double> v(0, 10);
	

	
	double sR = s(rnd);
	Vector3 p = iniPos + Vector3(pos(rnd), 0, pos(rnd));
	Vector3 vel = iniVel + Vector3(0, 0, 0);// Vector3(v(rnd), v(rnd), v(rnd));
	Vector3 size = iniSize + Vector3(sR, sR, sR);

	PxRigidDynamic* new_solid;
	new_solid = gPhyscis->createRigidDynamic(PxTransform(p));
	new_solid->setLinearVelocity(vel);
	new_solid->setAngularVelocity({ 0,0,0 });
	auto shape = CreateShape(PxBoxGeometry(size)); new_solid->attachShape(*shape);
	new_solid->setMassSpaceInertiaTensor({ size.y * size.z,size.x * size.z,size.x * size.y });
	new RenderItem(shape, new_solid, {0,0,1,1});
	gScene->addActor(*new_solid);

	forceRegistry->addRegistry(explosion, new_solid);
	forceRegistry->addRegistry(rotation, new_solid);
}

void WorldManager::update(double t)
{
	forceRegistry->updateForces(t);
	explosion->updateValues(t);
}

PxRigidDynamic* WorldManager::instanciatePlayer(Vector3 p, float size_)
{
	player = gPhyscis->createRigidDynamic(PxTransform(p));
	auto shape = CreateShape(PxSphereGeometry(size_)); 
	player->attachShape(*shape);

	//esto no se si ira asi
	Vector3 size = { size_, size_, size_ };
	player->setMassSpaceInertiaTensor({ size.y * size.z,size.x * size.z,size.x * size.y });


	new RenderItem(shape, player, { 0,0,1,1 });
	gScene->addActor(*player);

	return player;
}
