#pragma once
#include "ForceGenerator.h"
#include "core.hpp"
class GravityForceGenerator :public ForceGenerator
{
public:
    GravityForceGenerator(const Vector3& g);
    virtual ~GravityForceGenerator();
    //hereda
    virtual void updateForce(Particle* p, double t);

    inline void setGravity(const Vector3& g);

protected:
    Vector3 gravity;
};
