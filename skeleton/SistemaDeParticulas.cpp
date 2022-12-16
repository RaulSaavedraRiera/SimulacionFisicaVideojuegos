
#include "SistemaDeParticulas.h"
#include "FireWork.h"
#include "core.hpp"
#include "RenderUtils.hpp"
#include <PxScene.h>
#include "RigidBodyForceRegistry.h"
#include "PlayerController.h"

using namespace physx;

SistemaDeParticulas::SistemaDeParticulas()
{

	fountainP = new Particle({ 0 ,0, 0 }, { 0, 0, 0 }, 0.8, 5, { 0, 1, 1, 1 }, { 0, -2 , 0 }, 0.99);
	snowP = new Particle({ 0 ,0, 0 }, { 0, 0, 0 }, 0.6, 5, { 1, 1, 1, 1 }, { 0, -0.5 , 0 }, 0.99);
	laserP = new Particle({ 0 ,0, 0 }, { 0, 0, 0 }, 0.05, 2, { 1, 0.5, 0, 1 }, { 0, 0 , 0 }, 0.99);
	

	fuenteS.devTip_pos = { 1, 0, 1 }; fuenteS.devTip_vel = { 3, 0, 6 }; fuenteS.n_particles = 4; fuenteS.random = 1; fuenteS.randomPos = 0.2;
	snowS.pos_width = { 1, 0, 1 }; snowS.vel_width = { 6, 6, 6 }; snowS.n_particles = 4; snowS.random = 100; snowS.randomPos = 100;
	laserS.pos_width = { 1, 0, 1 }; laserS.vel_width = { 0, 25, 0 }; laserS.n_particles = 25; laserS.random = 0.1; laserS.randomPos = 3;


	gravity = new GravityForceGenerator({ 0, -9.8, 0 });
	forces.push_back(gravity);
	forceRegistry = new ParticleForceRegistry();


	//generadores

	wind = new UniformWindGenerator(1.2, 2, { 0, 10, 0 }, { -10, -10, 0 }, 100);

	whirlWind = new WhirlWindGenerator(2, { 0,10,0 }, 1000);


	explosion = new Explosion(500, 100, { 0, 10, 0 });
	explosion->change();



	//para los muelles
	slowGravity = new GravityForceGenerator({ 0, -1, 0 });

	cannonParticle = new Particle({ 0, 0, 0 }, { 0,0,0 }, 0.5, 5, { 1, 0, 0, 1 });
	cannonParticle->setCanColPlayer(true);
	dragParticle = new Particle({ 0, 0, 0 }, { 0,0,0 }, 0.75, 20, { 1, 0.5, 0, 1 });
	cannonParticle->setCanColPlayer(true);
	trailParticle = new Particle({ 0 ,0, 0 }, { 0, 0, 0 }, 0.05, 2, { 1, 0.5, 0, 1 }, { 0, 0 , 0 }, 0.99);

	cannonSystem.devTip_pos = { 0, 0, 0 }; cannonSystem.devTip_vel = { 10, 0, 0 }; cannonSystem.n_particles = 10; cannonSystem.random = 1; cannonSystem.randomPos = 0.2;
	dragSystem.devTip_pos = { 1, 0, 1 }; dragSystem.devTip_vel = { 0, 0, 0 }; dragSystem.n_particles = 3; dragSystem.random = 1; dragSystem.randomPos = 7;
	trail.pos_width = { 0, 0, 0 }; trail.vel_width = { 0, 0, 0 }; trail.n_particles = 25; trail.random = 0.1; trail.randomPos = 0.5;

}

SistemaDeParticulas::~SistemaDeParticulas()
{
	//deletear particulas moldes

	for (Particle* p : particles)
	{
		delete p;
		p = nullptr;
	}
	particles.clear();

	for (ParticleGenerator* g : generators)
	{
		delete g;
		g = nullptr;
	}
	generators.clear();
}

void SistemaDeParticulas::CreateParticleGenerator(TypeGenerator generator, Vector3 p, Vector3 v)
{

	for (ParticleGenerator* g : generators)
	{
		delete g;
		g = nullptr;
	}
	generators.clear();


	switch (generator)
	{
	case SistemaDeParticulas::fuente:
		generators.push_back(
			new GaussianParticleGenerator(this, "fuente", fountainP->clone(), fuenteS.n_particles, p, v, fuenteS.devTip_pos, fuenteS.devTip_vel, fuenteS.random, fuenteS.randomPos, 0));
		break;
	case SistemaDeParticulas::snow:
		generators.push_back(
			new UniformParticleGenerator(this, "snow", snowP->clone(), snowS.n_particles, p, v, snowS.pos_width, snowS.vel_width, snowS.random, snowS.randomPos));
		break;
	case SistemaDeParticulas::laser:
		generators.push_back(
			new UniformParticleGenerator(this, "laser", laserP->clone(), laserS.n_particles, p, v, laserS.pos_width, laserS.vel_width, laserS.random, laserS.randomPos));
		break;
	default:
		break;
	}


}

void SistemaDeParticulas::CreateFireWorkSystem(char c)
{
	shared_ptr<CircleParticleGenerator> gen1(new CircleParticleGenerator(this, "fireWork1",
		new Particle({ 0,0,0 }, { 0,0,0 }, 0.5, 3), 10, { 0,0,0 }, { 0, 0, 0 }));

	shared_ptr<CircleParticleGenerator> gen2(new CircleParticleGenerator(this, "fireWork2",
		new Particle({ 0,0,0 }, { 0,0,0 }, 0.5, 0.2, { 0,1,0,1 }, { 0,-0.02,0 }), 40, { 0,0,0 }, { 0, 0, 0 }, 0.2, 3));


	shared_ptr<CircleParticleGenerator> gen4(new CircleParticleGenerator(this, "fireWork4",
		new Particle({ 0,0,0 }, { 0,0,0 }, 0.3, 1, { 0,1,0,1 }, { 0,-0.3,0 }), 10, { 0,0,0 }, { 0, 0, 0 }));


	shared_ptr<CircleParticleGenerator> gen3(new CircleParticleGenerator(this, "fireWork3",
		new FireWork({ 0,0,0 }, { 0, 10, 0 }, 0.6, 3, { gen4 }, { 1, 0, 0, 1 }), 40, { 0,0,0 }, { 0, 0, 0 }, 4, 1));


	shared_ptr<CircleParticleGenerator> gen5(new CircleParticleGenerator(this, "fireWork5",
		new FireWork({ 0,0,0 }, { 0, 20, 0 }, 0.5, 1, { gen3 }, { 1, 0.5, 0, 1 }), 10, { 0,0,0 }, { 0, 0, 0 }, 0.2, 3));


	shared_ptr<UniformParticleGenerator> gen7(new UniformParticleGenerator(this, "fireWork7", new Particle({ 0,0,0 }, { 0,0,0 }, 0.3, 0.65),
		6, { 0, 0, 0 }, { 0, 0, 0 }, { 0,0,0 }, { 0, -2.5, 0 }, 10, 0.1));

	shared_ptr<UniformParticleGenerator> gen6(new UniformParticleGenerator(this, "fireWork6",
		new FireWork({ 0,0,0 }, { 0, 20, 0 }, 0.5, 1.25, { gen7 }, { 1, 0.5, 0, 1 }),
		10, { 0,0,0 }, { 0, 0, 0 }, { 0,0,0 }, { 0, 0, 0 }, 10, 0.1));


	//SistemaDeParticulas* s, string name, Particle* p, int n, Vector3 pos, Vector3 v, Vector3 wPos, Vector3 wVel, double rnd, double rndP





	if (c == 'E')
	{


		/*FireWork({ 0,0,0 }, { 0, 10, 0 }, 1, 3, {}),
		7, {0,0,0}, {0,0,0}));*/

		particles.push_back(new FireWork({ 0,0,0 }, { 0, 10, 0 }, 1, 3, { gen1 }, { 1, 0, 0, 1 }));
	}

	if (c == 'R')
	{
		particles.push_back(new FireWork({ 0,0,0 }, { 0, 15, 0 }, 1, 3, { gen2 }, { 0, 0, 1, 1 }));
	}

	if (c == 'T')
	{
		particles.push_back(new FireWork({ 0,0,0 }, { 0, 15, 0 }, 1, 3, { gen3 }, { 0, 0, 1, 1 }));
	}

	if (c == 'Y')
	{
		particles.push_back(new FireWork({ 0,0,0 }, { 0, 30, 0 }, 1, 3, { gen5 }, { 0, 1, 1, 1 }));
	}

	if (c == 'U')
	{
		particles.push_back(new FireWork({ 0,0,0 }, { 0, 30, 10 }, 1, 1, { gen6 }, { 0.5, 1, 1, 1 }));
	}
	if (c == 'I')
	{
		particles.push_back(new FireWork({ 0,0,0 }, { 0, 40, 0 }, 1, 1, { gen3, gen1 }, { 0.5, 1, 1, 1 }));
	}

}

void SistemaDeParticulas::CreatePhysicsParticle(char c)
{

	Particle* p;
	//forceRegistry->addRegistry(gravity, p);
	//forceRegistry->addRegistry(wind, p);
	std::default_random_engine rnd{ std::random_device{}() };
	std::uniform_real_distribution<float> interval(-20, 20);

	switch (c)
	{
	case 'z':
		p = new Particle({ 0 ,10, 0 }, { 0, 0, 0 }, 2, 20, { 1, 0, 1, 1 }, { 0, 0 , 0 }, 0.2);
		forceRegistry->addRegistry(gravity, p);
		break;

	case 'x':
		p = new Particle({ 0 ,10, 0 }, { 50, 50, 0 }, 2, 20, { 1, 1, 1, 1 }, { 0, 0 , 0 }, 0.2);
		forceRegistry->addRegistry(wind, p);;
		break;
	case 'c':
		p = new Particle({ -10 ,10, 0 }, { 0, 0, 0 }, 1, 20, { 0, 0, 1, 1 }, { 0, 0 , 0 }, 0.2);
		forceRegistry->addRegistry(whirlWind, p);
		break;
	case 'v':
		p = new Particle({ -0 ,10, 0 }, { 0, 0, 0 }, 0.5, 15, { 1, 0, 0, 1 }, { 0, 0 , 0 }, 0.2);
		p->setMass((rand() % 100) + 1);

		cout << p->getMass() << endl;

		p->changePos(interval(rnd), interval(rnd), interval(rnd));
		forceRegistry->addRegistry(explosion, p);
		break;

	default:
		break;
	}

	particles.push_back(p);
}

void SistemaDeParticulas::ControlForceGenerators(char c)
{


	switch (c)
	{
	case '1':
		gravity->changeEnabled();
		break;
	case '2':
		wind->changeEnable();
		break;
	case '3':
		whirlWind->changeEnable();
		break;
	case '4':
		explosion->change();
		break;
	case '5':
		GenerateSpringDemo();
		break;
	case '6':
		GenerateSpringDemo2Particles();
		break;
	case '7':
		GenerateSpringSlinkyDemo();
		break;
	case '8':
		GenerateFloatDemo();
		break;
	case '9':
		slowGravity->changeEnabled();
		break;
	case 'o':
		springIdle->setK(springIdle->getK() + 10);
		break;
	case 'p':
		spring1->setK(spring1->getK() + 1);
		spring2->setK(spring2->getK() + 1);
		break;
	default:
		break;
	}
	return;

}

void SistemaDeParticulas::GenerateSpringDemo()
{

	//para sin gravedad tienen que estar alejadas, p.x = -10 s.x = 10
	Particle* p1 = new Particle({ 0, 10, 0 }, { 0, 0, 0 }, 1, 99999, { 1, 0, 0, 1 }, { 0, 0 , 0 }, 0.99, 2, false);



	//5, 10 para no gravedad
	springIdle = new SpringForceGenerator(5, 15, { 0, 10, 0 });

	forceRegistry->addRegistry(springIdle, p1);
	forceRegistry->addRegistry(slowGravity, p1);

	particles.push_back(p1);

}

void SistemaDeParticulas::GenerateSpringDemo2Particles()
{


	Particle* p1 = new Particle({ 20, 25, 0 }, { 0, 0, 0 }, 1, 99999, { 1, 0, 0, 1 }, { 0, 0 , 0 }, 0.99, 2, false);
	Particle* p2 = new Particle({ -20, 25, 0 }, { 0, 0, 0 }, 1, 99999, { 0, 0, 1, 1 }, { 0, 0 , 0 }, 0.99, 2, false);

	spring1 = new SpringForceGenerator(1, 21, p2);
	spring2 = new SpringForceGenerator(1, 21, p1);

	forceRegistry->addRegistry(spring1, p1);
	forceRegistry->addRegistry(spring2, p2);

	forceRegistry->addRegistry(slowGravity, p1);
	forceRegistry->addRegistry(slowGravity, p2);

	particles.push_back(p1);
	particles.push_back(p2);
}

void SistemaDeParticulas::GenerateSpringSlinkyDemo()
{

	int lenghtValue = 6;
	double damping = 0.99;

	slowGravity->setGravity({ 0, -16, 0 });

	SpringForceGenerator* springBase = new SpringForceGenerator(55, lenghtValue, { 0, 70, 0 });

	Particle* p0 = new Particle({ 0, 65, 0 }, { 0, 0, 0 }, 1, 99999, { 1, 0, 0, 1 }, { 0, 0 , 0 }, damping, 2, false);
	particles.push_back(p0);
	Particle* p1 = new Particle({ 0, 60, 0 }, { 0, 0, 0 }, 1, 99999, { 0.8, 0, 0.2, 1 }, { 0, 0 , 0 }, damping, 2, false);
	particles.push_back(p1);
	Particle* p2 = new Particle({ 0, 55, 0 }, { 0, 0, 0 }, 1, 99999, { 0.5, 0, 0.5, 1 }, { 0, 0 , 0 }, damping, 2, false);
	particles.push_back(p2);
	Particle* p3 = new Particle({ 0, 50, 0 }, { 0, 0, 0 }, 1, 99999, { 0.5, 0, 0.5, 1 }, { 0, 0 , 0 }, damping, 2, false);
	particles.push_back(p3);
	Particle* p4 = new Particle({ 0, 45, 0 }, { 0, 0, 0 }, 1, 99999, { 0.2, 0, 0.8, 1 }, { 0, 0 , 0 }, damping, 2, false);
	particles.push_back(p4);
	Particle* p5 = new Particle({ 0, 40, 0 }, { 0, 0, 0 }, 1, 99999, { 0, 0, 1, 1 }, { 0, 0 , 0 }, damping, 2, false);
	particles.push_back(p5);

	forceRegistry->addRegistry(slowGravity, p0);
	forceRegistry->addRegistry(slowGravity, p1);
	forceRegistry->addRegistry(slowGravity, p2);
	forceRegistry->addRegistry(slowGravity, p3);
	forceRegistry->addRegistry(slowGravity, p4);
	forceRegistry->addRegistry(slowGravity, p5);
	//forceRegistry->addRegistry(slowGravity, p2);

	forceRegistry->addRegistry(springBase, p0);


	forceRegistry->addRegistry(new SpringForceGenerator(50, lenghtValue, p0), p1);

	forceRegistry->addRegistry(new SpringForceGenerator(45, lenghtValue, p1), p0);
	forceRegistry->addRegistry(new SpringForceGenerator(40, lenghtValue, p1), p2);

	forceRegistry->addRegistry(new SpringForceGenerator(35, lenghtValue, p2), p1);
	forceRegistry->addRegistry(new SpringForceGenerator(30, lenghtValue, p2), p3);

	forceRegistry->addRegistry(new SpringForceGenerator(25, lenghtValue, p3), p2);
	forceRegistry->addRegistry(new SpringForceGenerator(20, lenghtValue, p3), p4);

	forceRegistry->addRegistry(new SpringForceGenerator(15, lenghtValue, p4), p3);
	forceRegistry->addRegistry(new SpringForceGenerator(10, lenghtValue, p4), p5);

	forceRegistry->addRegistry(new SpringForceGenerator(10, lenghtValue, p5), p4);



	//SpringForceGenerator* spring;
	////forceRegistry->addRegistry(slowGravity, p);
	//
	//int y = 60;
	//for (int i = 0; i < 1; i++)
	//{
	//	y -= 10;
	//
	//	spring = new SpringForceGenerator(15, 20, p);
	//
	//	p = new Particle({ 0, (float)y, 0 }, { 0, 0, 0 }, 1, 99999, { 0, 1, 0, 1 }, { 0, 0 , 0 }, 0.8, 2, false);
	//	particles.push_back(p);
	//
	//	forceRegistry->addRegistry(spring, p);
	//
	//	
	//
	//
	//}
}

void SistemaDeParticulas::GenerateFloatDemo()
{

	if (floatG == nullptr) {
		floatG = new FloatGenerator(1, 1, 1000);

		hardGravity = new GravityForceGenerator({ 0, -9.8, 0 });
		hardGravity->changeEnabled();
	}



	std::default_random_engine rnd{ std::random_device{}() };
	std::uniform_real_distribution<double> sizeMass(0.75, 3);
	std::uniform_real_distribution<float> pos(-45, 45);

	double sM = sizeMass(rnd);
	Particle* p = new Particle({ pos(rnd), 5, pos(rnd) }, { 0, 0, 0 }, sM, 99999, { 1, 0, (float)(1 / sM), 1 }, { 0, 0 , 0 }, 0.35, 20, sM);
	p->setVolume(sM * sM * sM);
	particles.push_back(p);

	forceRegistry->addRegistry(floatG, p);
	forceRegistry->addRegistry(hardGravity, p);
}

void SistemaDeParticulas::Update(double t)
{
	//actualizamos los valores respecot al tiempo antes de la de las fuerzas a las particulas
	explosion->updateValues(t);

	forceRegistry->updateForces(t);

	auto i = particles.begin();

	while (i != particles.end()) {
		if (!(*i)->integrate(t)) {

			if (auto f = dynamic_cast<FireWork*>((*i)))
			{
				auto newsP = f->explode();

				for (auto n : newsP)
					particles.push_back(n);
			}

			delete (*i);
			i = particles.erase(i);
		}
		else i++;
	}


	for (auto i = generators.begin(); i != generators.end(); i++)
	{
		auto newP = (*i)->generateParticles(t);

		while (!newP.empty())
		{
			particles.push_back(newP.front());
			newP.pop_front();
		}


		newP.clear();
	}
}


void SistemaDeParticulas::CreateParticleCanon(Vector3 p, int dir) {

	Vector3 v = { dir * 7.f, 5, 0 };

	generators.push_back(
		new GaussianParticleGenerator(this, "cannon", cannonParticle->clone(), cannonSystem.n_particles, p, v, cannonSystem.devTip_pos, cannonSystem.devTip_vel, cannonSystem.random, cannonSystem.randomPos, 3));
}

void SistemaDeParticulas::CreateParticlesDrag(Vector3 p, int dir)
{
	//Vector3 v = { dir * 7.f, 5, 0 };
	Vector3 v = { 0, 0, 0 };

	list<ForceGenerator*> forcesInZone = list<ForceGenerator*>();

	/*forcesInZone.push_front(
		new UniformWindGenerator(20, 10, p, { dir * 10.f, 0, 0 }, 30));*/
	forcesInZone.push_front(
		new UniformWindGenerator(20, 10, p, { 0, -10.f, 0 }, 30));

	forcesInZone.front()->enabled = true;
	/*forcesInZone.push_front(
		explosion = new Explosion(10000, 20, { p.x + dir * 10, p.y, p.z - 15 }));*/
	forcesInZone.push_front(
		explosion = new Explosion(10000, 20, {p.x, p.y, p.z }));
	forcesInZone.front()->enabled = true;

	// { p.x - dir * 30, 5, p.z- 15 }
	auto g = new GaussianParticleGenerator(this, "dragZone", dragParticle->clone(), dragSystem.n_particles, { p.x, p.y+30, p.z }, v, dragSystem.devTip_pos, dragSystem.devTip_vel, dragSystem.random, dragSystem.randomPos, 2,
		forceRegistry, forcesInZone);

	g->setXRandomPosMod(2);
	g->setZRandomPosMod(2);
	g->setYRandomPosMod(0);
	generators.push_back(g);


}

void SistemaDeParticulas::CreateWaterZone(Vector3 pos, physx::PxRigidDynamic* player, RigidBodyForceRegistry* forces) {



	floatG = new FloatGenerator({pos.x, pos.y + 1, pos.z}, {30, 1, 25}, 1, 1000);

	hardGravity = new GravityForceGenerator({ 0, -9.8, 0 });
	hardGravity->enabled = true;


	forces->addRegistry(floatG, player);

	std::default_random_engine rnd{ std::random_device{}() };
	std::uniform_real_distribution<double> sizeMass(0.5, 1);
	std::uniform_real_distribution<float> posZ(-10, 10);
	std::uniform_real_distribution<float> posX(-20, 20);


	for (auto i = 0; i < waterParticlesN; i++)
	{
		double sM = sizeMass(rnd);
		Particle* p = new Particle({ posX(rnd) + pos.x, pos.y + 10, pos.z + posZ(rnd) }, { 0, 0, 0 }, sM, 99999, { 1, 0, (float)(1 / sM), 1 }, { 0, 0 , 0 }, 0.35, 20, sM * 15, true, true);
		p->setVolume(sM * sM * sM);
		particles.push_back(p);

		forceRegistry->addRegistry(floatG, p);
		forceRegistry->addRegistry(hardGravity, p);
	}

}

//muelles siempre al principio pq se van parando, poner 1 al priniipio
void SistemaDeParticulas::CreateBouncyZone(Vector3 p) {

	Particle* p1;

	p1 = new Particle({ p.x - 15, p.y+2, p.z-10 }, { 0, 0, 0 }, 1, 99999, { 1, 0, 0, 1 }, { 0, 0 , 0 }, 0.99, 2, false);
	springIdle = new SpringForceGenerator(5, 10, { p.x + 15, p.y + 2, p.z - 10 });
	forceRegistry->addRegistry(springIdle, p1);
	particles.push_back(p1);

	p1 = new Particle({ p.x + 15, p.y + 2, p.z }, { 0, 0, 0 }, 1, 99999, { 1, 0, 0, 1 }, { 0, 0 , 0 }, 0.99, 2, false);
	springIdle = new SpringForceGenerator(5, 10, { p.x - 15, p.y + 2, p.z});
	forceRegistry->addRegistry(springIdle, p1);
	particles.push_back(p1);

	p1 = new Particle({ p.x - 15, p.y + 2, p.z + 10 }, { 0, 0, 0 }, 1, 99999, { 1, 0, 0, 1 }, { 0, 0 , 0 }, 0.99, 2, false);
	springIdle = new SpringForceGenerator(5, 10, { p.x + 15, p.y + 2, p.z + 10 });
	forceRegistry->addRegistry(springIdle, p1);
	particles.push_back(p1);

}

void SistemaDeParticulas::ActualicePlayerTrail(Vector3 pos){

	if (trailPlayer == nullptr) {
		trailPlayer = new UniformParticleGenerator(this, "trail", trailParticle->clone(), trail.n_particles, pos, { 0,0,0 }, trail.pos_width, trail.vel_width, trail.random, trail.randomPos);
		generators.push_back(trailPlayer);
	}
		

	trailPlayer->ChangePos(pos);
}

bool SistemaDeParticulas::CheckParticlePlayerCollision(PlayerController* player)
{
	auto i = particles.begin();

	while (i != particles.end()) {

		if ((*i)->canColWithPlayer() && player->CollisionWithParticle((*i)->getPos(), { 1,1,1 }))
			return true;

		i++;
	}

	return false;
}

void SistemaDeParticulas::LaunchFireWorksWin(int zVal) {

	shared_ptr<CircleParticleGenerator> gen1(new CircleParticleGenerator(this, "fireWork1",
		new Particle({ 0,0,0 }, { 0,0,0 }, 0.5, 3), 10, { 0,0,0 }, { 0, 0, 0 }));

	shared_ptr<CircleParticleGenerator> gen2(new CircleParticleGenerator(this, "fireWork2",
		new Particle({ 0,0,0 }, { 0,0,0 }, 0.5, 0.2, { 0,1,0,1 }, { 0,-0.02,0 }), 40, { 0,0,0 }, { 0, 0, 0 }, 0.2, 3));


	shared_ptr<CircleParticleGenerator> gen4(new CircleParticleGenerator(this, "fireWork4",
		new Particle({ 0,0,0 }, { 0,0,0 }, 0.3, 1, { 0,1,0,1 }, { 0,-0.3,0 }), 10, { 0,0,0 }, { 0, 0, 0 }));


	shared_ptr<CircleParticleGenerator> gen3(new CircleParticleGenerator(this, "fireWork3",
		new FireWork({ 0,0,0 }, { 0, 10, 0 }, 0.6, 3, { gen4 }, { 1, 0, 0, 1 }), 40, { 0,0,0 }, { 0, 0, 0 }, 4, 1));


	shared_ptr<CircleParticleGenerator> gen5(new CircleParticleGenerator(this, "fireWork5",
		new FireWork({ 0,0,0 }, { 0, 20, 0 }, 0.5, 1, { gen3 }, { 1, 0.5, 0, 1 }), 10, { 0,0,0 }, { 0, 0, 0 }, 0.2, 3));

	shared_ptr<UniformParticleGenerator> gen7(new UniformParticleGenerator(this, "fireWork7", new Particle({ 0,0,0 }, { 0,0,0 }, 0.3, 0.65),
		6, { 0, 0, 0 }, { 0, 0, 0 }, { 0,0,0 }, { 0, -2.5, 0 }, 10, 0.1));

	shared_ptr<UniformParticleGenerator> gen6(new UniformParticleGenerator(this, "fireWork6",
		new FireWork({ 0,0,0 }, { 0, 20, 0 }, 0.5, 1.25, { gen7 }, { 1, 0.5, 0, 1 }),
		10, { 0,0,0 }, { 0, 0, 0 }, { 0,0,0 }, { 0, 0, 0 }, 10, 0.1));

	particles.push_back(new FireWork({ -20,0, zVal + 5.f}, { 0, 40, 0 }, 1, 1, { gen3, gen1 }, { 0.5, 1, 1, 1 }));
	particles.push_back(new FireWork({ 20,0, zVal + 5.f}, { 0, 40, 0 }, 1, 1, { gen3, gen1 }, { 0.5, 1, 1, 1 }));

	particles.push_back(new FireWork({ -15,0, zVal + 30.f }, { 0, 30, 0 }, 1, 3, { gen2 }, { 0, 1, 1, 1 }));
	particles.push_back(new FireWork({ 15,0, zVal + 30.f }, { 0, 30, 0 }, 1, 3, { gen2 }, { 0, 1, 1, 1 }));
}





