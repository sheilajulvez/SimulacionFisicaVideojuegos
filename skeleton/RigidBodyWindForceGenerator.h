#pragma once
#include "RigidBodyForceGenerator.h"
class RigidBodyWindForceGenerator:public RigidBodyForceGenerator
{
public:
    RigidBodyWindForceGenerator(Vector3 f, Vector3 ini_pos, Vector3 tam, const float k1, const float k2);
    virtual void updateForce(RigidBodyParticle* particle, double t) override;
    virtual ~RigidBodyWindForceGenerator();
   
    inline void setDrag(float k1, float k2) {
        _k1 = k1;
        _k2 = k2;
    }
    inline float getk1() { return _k1; }
    inline float getk2() { return _k2; }
    inline void setf(Vector3 f) { this->f = f; }

protected:
    Vector3 ini_pos;
    Vector3 longitud;
    Vector3 f;
    float _k1;  //coef velocity
    float _k2;  //coef square velocity
};

