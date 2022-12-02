#pragma once

#include <map>
#include "ForceGenerator.h"

typedef std::pair<ForceGenerator*, physx::PxRigidDynamic*> FRPairRigid;


class RigidBodyForceRegistry : public std::multimap<ForceGenerator*, physx::PxRigidDynamic*>
{
public:
    void updateForces(double duration)
    {
        for (auto it = begin(); it != end(); it++)
        {
            it->first->updateForceRigids(it->second, duration);
        }
    }

    void addRegistry(ForceGenerator* fg, physx::PxRigidDynamic* p) { this->insert(FRPairRigid(fg, p)); };

    void deleteParticleRegistry(physx::PxRigidDynamic* p)
    {
        for (auto it = begin(); it != end(); it++)
        {
            if (it->second == p)
            {
                erase(it);
            }
        }
    };
};