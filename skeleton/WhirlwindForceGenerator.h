#pragma once
#include "WindForceGenerator.h"
class WhirlwindForceGenerator:public WindForceGenerator
{
public:
	WhirlwindForceGenerator(Vector3 f, Vector3 ini_pos, Vector3 tam, const float k1, const float k2);
	virtual ~WhirlwindForceGenerator();
	virtual void updateForce(Particle* particle, double t) override;
};

