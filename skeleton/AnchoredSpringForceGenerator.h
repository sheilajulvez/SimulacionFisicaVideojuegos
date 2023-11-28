#pragma once
#include "SpringForceGenerator.h"

class AnchoredSpringForceGenerator:public SpringForceGenerator{
public: 
	AnchoredSpringForceGenerator(double k, double resting, const Vector3& anchor_pos);
	virtual ~AnchoredSpringForceGenerator();
	inline void setk(double k) { _k = k; };
	inline double getk() { return _k; };
private:
	physx::PxTransform trans;
	RenderItem* renderItem;
};

