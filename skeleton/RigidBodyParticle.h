#pragma once
#include <PxScene.h>
#include <PxPhysics.h>
#include "RenderUtils.hpp"
#include <iostream>
using namespace physx;
const float DAMPINGRB = 0.998;
class RigidBodyParticle
{
private:
	float masa, invMasa;
	float timeOfLife = 3, time;
	bool death = false;
	// Accumulated force
	Vector3 force;
	physx::PxVec3	mDir;
	physx::PxVec3	mAcel;

	PxPhysics* gPhysicsRB = nullptr;
	PxScene* gSceneRB = nullptr;
	PxRigidStatic* staticRB = nullptr;
	PxRigidDynamic* dynamicRB = nullptr;
	RenderItem* rItem = nullptr;
	bool soypelota = false;
	
public:
	RigidBodyParticle(PxPhysics* gPhysics_, PxScene* gScene_, RenderItem* rItem_, PxRigidStatic* statico);	
	RigidBodyParticle(PxPhysics* gPhysics_, PxScene* gScene_, RenderItem* rItem_, PxRigidDynamic* dynamico);
	~RigidBodyParticle() {};

	void integrate(double t);

	// Add force to apply in next integration only
	void addForce(Vector3 f);
	void addForceLinear(Vector3 f);
	// Clears accumulated force
	void clearForce();

	float getInvMss();

	Vector3 getDir();
	inline float getMass() { if (dynamicRB != nullptr) return dynamicRB->getMass(); };
	inline bool getsoypelota() { return soypelota; }
	inline void setpelota() { soypelota = true; }
	inline PxTransform getTrans(){
		if(dynamicRB!= nullptr) return dynamicRB->getGlobalPose();
	}
	inline bool soydinamico() {
		return dynamicRB != nullptr;
	}
	inline PxRigidDynamic* dinamico() {
		if (dynamicRB != nullptr)return dynamicRB;
		
	}
	inline PxRigidStatic* estatico() {
		if (staticRB != nullptr)return staticRB;

	}
};

