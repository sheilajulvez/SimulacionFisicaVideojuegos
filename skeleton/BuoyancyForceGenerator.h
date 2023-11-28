#pragma once
#include "ForceGenerator.h"
#include "core.hpp"
class BuoyancyForceGenerator:public ForceGenerator
{
	BuoyancyForceGenerator(float h, float V, float d);
	virtual ~BuoyancyForceGenerator();
protected:
	float height, volume, liquid_density, gravity = 9.8;
	Particle* liquid_particle;
};

