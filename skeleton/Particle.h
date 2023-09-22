#pragma once
#include "PxPhysics.h"
#include "RenderUtils.hpp"
class Particle
{
public:
	Particle(Vector3 pos, Vector3 vel);
	~Particle();
	void integrate(double t);
private:
	Vector3 vel;
	physx::PxTransform trans;
	RenderItem* renderItem;


};

