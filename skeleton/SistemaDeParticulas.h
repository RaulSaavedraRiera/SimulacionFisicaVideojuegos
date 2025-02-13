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

//muelles
#include "SpringForcegenerator.h"
#include "FloatGenerator.h"

class RigidBodyForceRegistry;
class PlayerController;
 
class SistemaDeParticulas
{
public:


	enum TypeGenerator { fuente, firework, snow, laser };

	SistemaDeParticulas();
	~SistemaDeParticulas();

	void CreateParticleGenerator(TypeGenerator generator, Vector3 p, Vector3 v);

	void CreateFireWorkSystem(char c);

	void CreatePhysicsParticle(char c);

	void ControlForceGenerators(char c);

	void GenerateSpringDemo();
	void GenerateSpringDemo2Particles();
	void GenerateSpringSlinkyDemo();
	void GenerateFloatDemo();

	void Update(double t);

	void CreateParticleCanon(Vector3 p, int dir);
	void CreateParticlesDrag(Vector3 p, int dir);
	void CreateWaterZone(Vector3 p, physx::PxRigidDynamic* player, RigidBodyForceRegistry* forces);
	void CreateBouncyZone(Vector3 p);

	void ActualicePlayerTrail(Vector3 pos);
	bool CheckParticlePlayerCollision(PlayerController* player);
	void LaunchFireWorksWin(int zVal);

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


	FloatGenerator* floatG = nullptr;
	GravityForceGenerator* slowGravity = nullptr;
	GravityForceGenerator* hardGravity = nullptr;

	SpringForceGenerator* springIdle;

	SpringForceGenerator* spring1;
	SpringForceGenerator* spring2;


	//para practica final
	Particle* cannonParticle;
	GausianSystem cannonSystem;
	Particle* dragParticle;
	GausianSystem dragSystem;
	UniformSystem trail;
	Particle* trailParticle;

	UniformParticleGenerator* trailPlayer = nullptr;

	const int waterParticlesN = 10;
};

