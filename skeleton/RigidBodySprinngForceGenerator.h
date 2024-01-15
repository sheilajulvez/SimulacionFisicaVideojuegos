#pragma once
#include "RigidBodyForceGenerator.h"

#include "core.hpp"
class RigidBodySprinngForceGenerator : public RigidBodyForceGenerator {
public:
	RigidBodySprinngForceGenerator(double k, double resting_length, RigidBodyParticle* other, Vector3 pos );
	virtual void updateForce(RigidBodyParticle* particle, double t) override;
	inline void setk(double k) { _k = k; }
	virtual ~RigidBodySprinngForceGenerator();

protected:
	double _k; // Elastic Coeff.
	double _resting_length;
	RigidBodyParticle* _other;
	Vector3 pos;
};

