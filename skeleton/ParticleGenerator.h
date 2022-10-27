#pragma once
#include "Particle.h"
#include <string>
#include <list>
#include <random>
using namespace std;

class SistemaDeParticulas;

class ParticleGenerator
{
	
public:

	string name;

	ParticleGenerator(SistemaDeParticulas* s, string name, Particle* p, int n, Vector3 pos, Vector3 vel, double rnd = 1, double rndPos = 1);
	~ParticleGenerator();

	
	void setParticle(Particle* model) { this->model = model; };

	virtual list<Particle*> generateParticles(double t) = 0;

	void ChangePos(Vector3 newP) { model->pos.p = newP; }

protected:



	Vector3 meanPos, meanVel;

	double generationProbably, random, randomPos;
	int num_particles;

	Particle* model;

	SistemaDeParticulas* particleSystem;

	double timeGenerate, lastGenerate, currentTime;


};

