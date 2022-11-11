#pragma once
#include <vector>
#include <list>


#include "ParticleForceRegistry.h"
#include "GravityForceGenerator.h"
#include "UniformWindGenerator.h"
#include "WhirlWindGenerator.h"
#include "Explosion.h"

#include "GaussianParticleGenerator.h"
#include "UniformParticleGenerator.h"
#include "CircleParticleGenerator.h"

//tios de particulas que usaremos
#include "CanonBall.h"

class SistemaDeParticulas
{
public:


	enum TypeGenerator { fuente, firework, snow, laser };

	SistemaDeParticulas();
	~SistemaDeParticulas();

	void CreateParticleGenerator(TypeGenerator generator, Vector3 p, Vector3 v);

	void CreateFireWorkSystem(char c);

	void CreatePhysicsParticle(char c);


	void ActivateExplosion();

	void Update(double t);
	
protected:

	
	//plantillas de particula
	Particle* fountainP;
	Particle* snowP;
	Particle* laserP;
	

	std::list<ParticleGenerator*> generators;
	std::list<ForceGenerator*> forces;
	std::list<Particle*> particles;

	struct GausianSystem {
		Vector3 devTip_pos;
		Vector3 devTip_vel;
		int n_particles;
		double random;
		double randomPos;
	};

	struct UniformSystem {
		Vector3 pos_width;
		Vector3 vel_width;
		int n_particles;
		double random;
		double randomPos;
	};

	GausianSystem fuenteS;
	UniformSystem snowS;
	UniformSystem laserS;

	ParticleForceRegistry* forceRegistry;
	GravityForceGenerator* gravity;
	UniformWindGenerator* wind;
	WhirlWindGenerator* whirlWind;
	Explosion* explosion;
};

