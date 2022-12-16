#pragma once
#include "ForceGenerator.h"
class HorizontalForceGenerator :
    public ForceGenerator
{
public:
    HorizontalForceGenerator(double k, double t, double positiveIni);
    ~HorizontalForceGenerator() = default;

    virtual void updateForce(Particle* particle, double t) {};
    virtual void updateForceRigids(physx::PxRigidDynamic* particle, double t);

    void change() { enabled = !enabled; };

protected:

    double k, time;
    double lastChange, currentTime;

    bool left = false;
};

