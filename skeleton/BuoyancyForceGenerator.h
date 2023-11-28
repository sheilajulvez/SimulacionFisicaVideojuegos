#pragma once
#include "ForceGenerator.h"
#include "core.hpp"
class BuoyancyForceGenerator:public ForceGenerator
{
public:
	BuoyancyForceGenerator(float h, float V, float d, const Vector3& pos);
	virtual ~BuoyancyForceGenerator();
	virtual void updateForce(Particle* particle, double t) override;
protected:
	float height, volume, liquid_density, gravity = 9.8;

	physx::PxTransform trans;
	RenderItem* renderItem;
};

