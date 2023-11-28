#include "AnchoredSpringForceGenerator.h"
#include "PxPhysics.h"
#include "RenderUtils.hpp"
AnchoredSpringForceGenerator::AnchoredSpringForceGenerator(double k, double resting, const Vector3& anchor_pos) :
	SpringForceGenerator(k, resting, new Particle(anchor_pos, { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 }, 1, { 1.0, 0.0, 0.0,0 }, 1.0, 0, 2.0)), trans(anchor_pos)
{
	//CreateShape(physx::PxSphereGeometry(radio)), &trans, color
	Vector3 radio = { 5,5,5 };
	renderItem=new RenderItem(CreateShape(physx::PxBoxGeometry(radio)), &trans, { 0.4,0.3,0.9,0.5 });
	
}

AnchoredSpringForceGenerator::~AnchoredSpringForceGenerator() {
	DeregisterRenderItem(renderItem);
}