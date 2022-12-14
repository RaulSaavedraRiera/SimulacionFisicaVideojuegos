#include "WorldManager.h"
#include <random>
#include "PlayerController.h"

using namespace std;
WorldManager::WorldManager(PxPhysics* p, PxScene* s) : gPhyscis(p), gScene(s)
{
	generators = list<RigidBodyforceGenerator*>();
	rigids = list<PxRigidDynamic*>();

	forceRegistry = new RigidBodyForceRegistry();

	//generateRotationZone({ 0, 0, 0 });
	generateHorizontalWallsZone({ 0,0,5 });
}

WorldManager::~WorldManager()
{
	generators.clear();
	rigids.clear();
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
		//explosion->change();
		break;
	case 'm':
		//rotation->change();
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
	new RenderItem(shape, Suelo, { 0.8, 0.8, 0.8, 1 });
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
	new RenderItem(shape, new_solid, { 0,0,1,1 });
	gScene->addActor(*new_solid);



	/*forceRegistry->addRegistry(explosion, new_solid);
	forceRegistry->addRegistry(rotation, new_solid);*/
}

void WorldManager::update(double t)
{
	forceRegistry->updateForces(t);
	//explosion->updateValues(t);

	for (auto g : generators)
		generateRigids(g->generateBodies(t), g->getForces());

	if (player->getGlobalPose().p.y < minY)
		controller->resetPosition();
}

PxRigidDynamic* WorldManager::instanciatePlayer(PlayerController* c, Vector3 p, float size_)
{
	controller = c;

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

void WorldManager::generateZone1()
{
	PxRigidStatic* Suelo = gPhyscis->createRigidStatic(PxTransform({ 0, 0, 65 }));
	PxShape* shape = CreateShape(PxBoxGeometry(30, 1, 150));
	Suelo->attachShape(*shape);
	new RenderItem(shape, Suelo, { 0.5, 0.5, 0.5, 1 });
	gScene->addActor(*Suelo);
}

void WorldManager::generateFloor(Vector3 pos) {
	PxRigidStatic* Suelo = gPhyscis->createRigidStatic(PxTransform(pos));
	//random entre esto o cubo
	PxShape* shape = CreateShape(PxBoxGeometry(sizeZoneX, 1, sizeZoneZ));
	Suelo->attachShape(*shape);
	new RenderItem(shape, Suelo, { 0.8, 0.8, 0.8, 1 });
	gScene->addActor(*Suelo);
}

void WorldManager::generateRotationZone(Vector3 pos)
{
	generateFloor(pos);

	list<ForceGenerator*> forces = list<ForceGenerator*>();
	forces.push_back(new RotationGenerator(10, 30, pos));
	generators.push_back(new UniformRigidBodyGenerator(this, forces, "rotation", { pos.x, pos.y + 10, pos.z }, { 0, 0, 0 }, 0.5, 1, 15, 1, gPhyscis, 0.3, 1));

}

void WorldManager::generateHorizontalWallsZone(Vector3 pos)
{
	generateFloor(pos);

	list<ForceGenerator*> forces = list<ForceGenerator*>();
	int dir = rand() % 2;
	forces.push_back(new HorizontalForceGenerator(15, 7, dir == 1));

	if (dir == 1)
		generators.push_back(new StaticRigidBodyGenerator(this, forces, "walls", { pos.x - 10, pos.y + 3, pos.z }, 2, 0.5, gPhyscis, 1));
	else
		generators.push_back(new StaticRigidBodyGenerator(this, forces, "walls", { pos.x + 10, pos.y + 3, pos.z }, 2, 0.5, gPhyscis, 1));

}

void WorldManager::generateRigids(std::list<PxRigidDynamic*> d, std::list<ForceGenerator*> generatorsAttached) {

	for (auto dynamic : d) {

		gScene->addActor(*dynamic);
		for (auto g : generatorsAttached)
			forceRegistry->addRegistry(g, dynamic);
	}
	
		
	generatorsAttached.clear();
	d.clear();
}
