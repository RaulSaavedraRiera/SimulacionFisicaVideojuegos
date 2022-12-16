#include "FloatGenerator.h"




FloatGenerator::FloatGenerator(float h, float v, float d) 
	: _height(h), _volume(v), _liquid_density(d)
{
	_liquid_particle = new Particle({ 0, 0, 0 }, 50);

	_liquid_particle->setPos({ 0, 0, 0 });
}

FloatGenerator::~FloatGenerator()
{
	delete _liquid_particle;
	_liquid_particle = nullptr;
}

void FloatGenerator::updateForce(Particle* p, double t)
{
    float h = p->getPos().y;
    float h0 = _liquid_particle->getPos().y;

    Vector3 f(0, 0, 0);
    float immersed = 0.0;

    if (h - h0 > _height * 0.5)
    {
        immersed = 0.0;
    }
    else if (h0 - h > _height * 0.5) {
        immersed = 1.0;
    }
    else
    {
        immersed = (h0 - h) / _height + 0.5;
    }

    f.y = _liquid_density * p->getVolume() * immersed * 9.8;

    p->addForce(f);

}
