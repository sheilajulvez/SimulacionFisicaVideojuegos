#pragma once
#include "ForceGenerator.h"
class DragForceGenerator :public ForceGenerator
{
public:
    DragForceGenerator(const float k1, const float k2);
    virtual ~DragForceGenerator();
    virtual void updateForce(Particle* particle, double t);
    inline void setDrag(float k1, float k2) { _k1 = k1;
                                              _k2 = k2; }
    inline float getk1() { return _k1; }
    inline float getk2() { return _k2; }
    
protected:
    float _k1;  //coef velocity
    float _k2;  //coef square velocity
};
