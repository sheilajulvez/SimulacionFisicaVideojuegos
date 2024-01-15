#pragma once
#include <map>
#include "RigidBodyParticle.h"
#include "RigidBodyForceGenerator.h"

typedef pair<RigidBodyForceGenerator*, RigidBodyParticle*> RBFNPair;

class RigidBodyForceRegistry : public multimap<RigidBodyForceGenerator*, RigidBodyParticle*>
{
public:
	void updateForces(double duration);

	void addRegistry(RigidBodyForceGenerator* fg, RigidBodyParticle* rb);

	void deleteRegistry(RigidBodyForceGenerator* fg, RigidBodyParticle* rb);

	void deleteParticleRegistry(RigidBodyParticle* rb);
};