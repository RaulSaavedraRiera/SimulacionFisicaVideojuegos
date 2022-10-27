#include "CircleParticleGenerator.h"

CircleParticleGenerator::CircleParticleGenerator(SistemaDeParticulas* s, string name, Particle* p, int n, Vector3 pos, Vector3 v, double rndV, double rndP) :
	GaussianParticleGenerator(s, name, p, n, pos, v, {0, 0, 0}, {0, 0, 0}, rndV, rndP)
{

}
