#pragma once
#include "ForceGenerator.h"
class RotationGenerator :
    public ForceGenerator
{
public:
    RotationGenerator(double k, double R, Vector3 p);
    ~RotationGenerator() = default;

    virtual void updateForce(Particle* particle, double t) {};
    virtual void updateForceRigids(physx::PxRigidDynamic* particle, double t);

    void change() { enable = !enable; };

protected:

    bool enable = false;

    double k, R;
    Vector3 point;

};

