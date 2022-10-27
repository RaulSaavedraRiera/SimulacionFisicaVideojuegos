#include "UniformParticleGenerator.h"

UniformParticleGenerator::UniformParticleGenerator(SistemaDeParticulas* s, string name, Particle* p, int n, Vector3 pos, Vector3 v, Vector3 wPos, Vector3 wVel, double rnd, double rndP)
	: ParticleGenerator(s, name, p, n, pos, v, rnd, rndP), pos_width(wPos), vel_width(wVel)
{
	d = uniform_real_distribution<double>{ 0, random };
	dP = uniform_real_distribution<double>{ 0, randomPos };

}

list<Particle*> UniformParticleGenerator::generateParticles(double t)
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
			particles.front()->pos.p += Vector3(pos_width.x + dP(gnd), pos_width.y + dP(gnd), pos_width.z + dP(gnd));
			particles.front()->vel += Vector3(vel_width.x + d(gnd), vel_width.y + d(gnd), vel_width.z + d(gnd));
		}

		return particles;



	}

	return particles;

}
