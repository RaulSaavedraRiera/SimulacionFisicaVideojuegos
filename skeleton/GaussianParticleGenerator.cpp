#include "GaussianParticleGenerator.h"



GaussianParticleGenerator::GaussianParticleGenerator(SistemaDeParticulas* s, string name, Particle* p, int n, Vector3 pos, Vector3 v, Vector3 vTip_pos, Vector3 vTip_vel, double rnd, double rndPos, double timeGenerate, ParticleForceRegistry* r, std::list<ForceGenerator*> f)
	: ParticleGenerator(s, name, p, n, pos, v, rnd, rndPos, timeGenerate), devTip_pos(vTip_pos), devTip_vel(vTip_vel), registry(r), forces(f)
{
	d = normal_distribution<double>{0, rnd};
	dP = normal_distribution<double>{ 0, rndPos };

	xRandomMod = 1;
	yRandomMod = 1;
	zRandomMod = 1;
}

list<Particle*> GaussianParticleGenerator::generateParticles(double t)
{
	currentTime += t;
	list<Particle*> particles = list<Particle*>();

	//si el tiempo ha pasado se genera la nueva tanda
	if (timeGenerate + lastGenerate <= currentTime)
	{
		//actualziamos tiempos
		lastGenerate = currentTime;

		//creacion de particulas

		std:random_device r;
		default_random_engine gnd(r());

		int direction;
		if (model->getPos().x < 0)
			direction = 1;
		else
			direction = -1;
		for (auto i = 0; i < num_particles; i++)
		{
			particles.push_front(model->clone());
			particles.front()->pos.p += Vector3(devTip_pos.x + dP(gnd) * xRandomMod, devTip_pos.y + dP(gnd) * yRandomMod, devTip_pos.z + dP(gnd) * zRandomMod);
			particles.front()->vel += Vector3(direction * devTip_vel.x + d(gnd), devTip_vel.y + d(gnd), devTip_vel.z + d(gnd));
			particles.front()->setMass(rand() % 20 + 10);

			if (forces.size() > 0)
				for (auto f : forces)
					registry->addRegistry(f, particles.front());
		}

		return particles;



	}

	return particles;


}
