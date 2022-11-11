
#include "SistemaDeParticulas.h"
#include "FireWork.h"

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

	wind = new UniformWindGenerator(0.4, 0.8, { 0, 10, 0 }, { -10, -10, 0 }, 10);

	whirlWind = new WhirlWindGenerator(2, { 0,10,0 }, 1000);


	explosion = new Explosion(500, 100, { 0, 10, 0 });



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
			new GaussianParticleGenerator(this, "fuente", fountainP->clone(), fuenteS.n_particles, p, v, fuenteS.devTip_pos, fuenteS.devTip_vel, fuenteS.random, fuenteS.randomPos));
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
	if (c == 'v')
	{
		explosion->on();
		return;
	}

	
	Particle* p;
	//forceRegistry->addRegistry(gravity, p);
	//forceRegistry->addRegistry(wind, p);
	std::default_random_engine rnd{ std::random_device{}() };
	std::uniform_real_distribution<float> interval(-5, 5);

	switch (c)
	{
	case 'z':
		p = new Particle({ -10 ,10, 0 }, { 0, 0, 0 }, 2, 20, { 1, 1, 1, 1 }, { 0, 0 , 0 }, 0.2);
		forceRegistry->addRegistry(whirlWind, p);;
		break;
	case 'x':
		p = new Particle({ 0 ,10, 0 }, { 0, 0, 0 }, 2, 20, { 1, 1, 1, 1 }, { 0, 0 , 0 }, 0.2);
		forceRegistry->addRegistry(wind, p);
		break;
	case 'c':
		p = new Particle({ -0 ,10, 0 }, { 0, 0, 0 }, 0.5, 20, { 1, 0, 0, 1 }, { 0, 0 , 0 }, 0.2);
		p->changePos(interval(rnd), interval(rnd), interval(rnd));
		forceRegistry->addRegistry(explosion, p);
		break;
	default:
		break;
	}

	particles.push_back(p);
}

void SistemaDeParticulas::ActivateExplosion()
{
	explosion->on();
}

void SistemaDeParticulas::Update(double t)
{
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




