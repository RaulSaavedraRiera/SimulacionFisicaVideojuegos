#include "UniformRigidBodyGenerator.h"
#include <iostream>


UniformRigidBodyGenerator::UniformRigidBodyGenerator(WorldManager* s, list<ForceGenerator*> forcesAttach, string n, Vector3 p, Vector3 v, double iniS, double rndV, double rndP, double rndS, PxPhysics* gP, double tBS, double nS) :
	name(n), worldManager(s), pos(p), vel(v), randomSize(rndS), randomPos(rndP), randomVel(rndV), iniSize(iniS), gPhyscis(gP), timeBtwSpawn(tBS), nSpawn(nS), forces(forcesAttach)
{
	currentTime = 0;
	lastSpawn = 0;
	forcesAttach.clear();
}

list<PxRigidDynamic*> UniformRigidBodyGenerator::generateBodies(double t)
{

	list<PxRigidDynamic*> dynamics = list<PxRigidDynamic*>();

	currentTime += t;



	if (maxN > currentN && lastSpawn + timeBtwSpawn <= currentTime) {

		lastSpawn = currentTime;
		currentN += nSpawn;


		std::default_random_engine rnd{ std::random_device{}() };
		std::uniform_real_distribution<double> posVar(-randomPos, randomPos);
		std::uniform_real_distribution<double> s(0, randomSize);
		std::uniform_real_distribution<double> v(-randomVel, randomVel);

		for (auto i = 0; i < nSpawn; i++)
		{

			double sR = s(rnd);
			Vector3 p = pos + Vector3(posVar(rnd), 0, posVar(rnd));
			Vector3 velD = vel + Vector3(v(rnd), +2, v(rnd));
			Vector3 size = Vector3((double)iniSize, (double)iniSize, (double)iniSize) + Vector3(sR, sR, sR);

			dynamics.push_front(gPhyscis->createRigidDynamic(PxTransform(p)));

			dynamics.front()->setLinearVelocity(velD);
			dynamics.front()->setAngularVelocity({ 0,0,0 });
			PxShape* shape;
			rand() % 2 == 1 ? shape = CreateShape(PxBoxGeometry(size)) : shape = CreateShape(PxSphereGeometry(size.x));

			dynamics.front()->attachShape(*shape);
			dynamics.front()->setMassSpaceInertiaTensor({ size.y * size.z,size.x * size.z,size.x * size.y });
			new RenderItem(shape, dynamics.front(), { 0,0,1,1 });

		}

	}


	return dynamics;

}
