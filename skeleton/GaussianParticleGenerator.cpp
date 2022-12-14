#include "GaussianParticleGenerator.h"



GaussianParticleGenerator::GaussianParticleGenerator(SistemaDeParticulas* s, string name, Particle* p, int n, Vector3 pos, Vector3 v, Vector3 vTip_pos, Vector3 vTip_vel, double rnd, double rndPos, double timeGenerate)
	: ParticleGenerator(s, name, p, n, pos, v, rnd, rndPos, timeGenerate), devTip_pos(vTip_pos), devTip_vel(vTip_vel)
{
	d = normal_distribution<double>{0, rnd};
	dP = normal_distribution<double>{ 0, rndPos };
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
		for (auto i = 0; i < num_particles; i++)
		{
			particles.push_front(model->clone());
			particles.front()->pos.p += Vector3(devTip_pos.x + dP(gnd), devTip_pos.y + dP(gnd), devTip_pos.z + dP(gnd));
			particles.front()->vel += Vector3(devTip_vel.x + d(gnd), devTip_vel.y + d(gnd), devTip_vel.z + d(gnd));
			particles.front()->setMass(rand() % 20 + 10);
		}

		return particles;



	}

	return particles;


}
