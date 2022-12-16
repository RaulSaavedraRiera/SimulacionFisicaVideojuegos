#include "StaticRigidBodyGenerator.h"

StaticRigidBodyGenerator::StaticRigidBodyGenerator(WorldManager* s, list<ForceGenerator*> forcesAttach, string n, Vector3 p, double iniS, double rndS, PxPhysics* gP, double tBS) : worldManager(s), forces(forcesAttach), name(n),
pos(p), iniSize(iniS), randomSize(rndS), gPhyscis(gP), timeBtwSpawn(tBS)
{
	currentTime = 0;
	lastSpawn = -1;

}


list<PxRigidDynamic*> StaticRigidBodyGenerator::generateBodies(double t)
{

	list<PxRigidDynamic*> dynamics = list<PxRigidDynamic*>();

	currentTime += t;



	if (maxN > currentN && lastSpawn + timeBtwSpawn <= currentTime) {

		lastSpawn = currentTime;
		currentN += 3;

		for (int i = 0; i < 3; i++)
		{
			std::default_random_engine rnd{ std::random_device{}() };

			std::uniform_real_distribution<double> s(0, randomSize);



			double sR = s(rnd);
			Vector3 size = Vector3((double)iniSize, (double)iniSize, (double)iniSize) + Vector3(sR, sR, sR);

			dynamics.push_front(gPhyscis->createRigidDynamic(PxTransform(pos - Vector3( -15 + 15 * i, 0, 0 ))));

			dynamics.front()->setLinearVelocity({ 0,0,0 });
			dynamics.front()->setAngularVelocity({ 0,0,0 });
			dynamics.front()->setMaxAngularVelocity(0);

			auto shape = CreateShape(PxBoxGeometry(size)); dynamics.front()->attachShape(*shape);
			dynamics.front()->setMassSpaceInertiaTensor({ size.y * size.z,size.x * size.z,size.x * size.y });
			new RenderItem(shape, dynamics.front(), { 0,0,0,1 });
		}
		

	}


	return dynamics;

}