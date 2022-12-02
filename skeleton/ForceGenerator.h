#pragma once

#include "Particle.h"
#include <PxPhysics.h>
#include <list>
#include <random>

class ForceGenerator
{
public:
    ForceGenerator();
    ~ForceGenerator();

    virtual void updateForce(Particle* particle, double duration) = 0;
    virtual void updateForceRigids(physx::PxRigidDynamic* particle, double duration) {};
    std::string _name;
    double t = -1e10;
};