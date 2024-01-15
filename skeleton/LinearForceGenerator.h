#pragma once
#include "RigidBodyForceGenerator.h"
class LinearForceGenerator:public RigidBodyForceGenerator
{
public:
	LinearForceGenerator();
	virtual ~LinearForceGenerator();
	void updateForce(RigidBodyParticle* rb, double duration);
	Vector3 dir;
	inline  void setdir(Vector3 const& d) { dir = d; }
	inline Vector3 getdir() { return dir; }
};

