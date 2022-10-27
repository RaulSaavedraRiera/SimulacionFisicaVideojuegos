#include "FireWork.h"
#include "CircleParticleGenerator.h"

FireWork::FireWork(Vector3 pos_, Vector3 vel_, float size_, double tDestroy, std::list<std::shared_ptr<ParticleGenerator>> g, Vector4 color, Vector3 acc_, float damping_) :
	Particle(pos_, vel_, size_, tDestroy, color, acc_, damping_)
{


	for (auto gen : g)
		_gens.push_back(gen);


}

list<Particle*> FireWork::explode()
{
	list<Particle*> particles;

	for (auto s : _gens)
	{
		s->ChangePos(pos.p);

		for (auto p : s->generateParticles(0))
			particles.push_back(p);
	}


	return particles;

}
