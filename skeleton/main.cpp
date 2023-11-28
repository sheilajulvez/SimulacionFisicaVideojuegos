#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"
#include "SystemParticle.h"
#include <iostream>
#include <list>

std::string display_text = "Practica Sheila Julvez";


using namespace physx;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation* gFoundation = NULL;
PxPhysics* gPhysics = NULL;


PxMaterial* gMaterial = NULL;

PxPvd* gPvd = NULL;

PxDefaultCpuDispatcher* gDispatcher = NULL;
PxScene* gScene = NULL;
ContactReportCallback gContactReportCallback;
//std::list<Particle*>particulas;
SystemParticle* systemparticle=nullptr;
using namespace std;
//std::vector<Particle*> particulas;
// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport, PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(), true, gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);
	systemparticle = new SystemParticle();

}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);

	gScene->simulate(t);
	gScene->fetchResults(true);
	systemparticle->update(t);
	
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();

	gFoundation->release();
	delete(systemparticle);
}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	switch (toupper(key))
	{
	case 'P': {
		//Particula generador gausiana distribucion 1
 	  systemparticle->generateParticle(1, GetCamera()->getEye() + Vector3(-100, -100, -100), 
			Vector3(0, 10, 0) , Vector3(0, 9.8, 0), 2, 3, Vector4{ 0.749,0.800,0,1 }, 4);
		break;
	}
	case 'O': {
		//Particula generador gausiano distribucion 2
		systemparticle->generateParticle(2, GetCamera()->getEye()+Vector3(-40,-40,-40),
			Vector3(0, 1, 0) * 40, Vector3(0, 0, 0), 0.5f, 1, Vector4{ 1,0,0,1 }, 1);
		break;
	}
	case 'I':
	{	//Particula generador simple 
		systemparticle->generateParticle(3, GetCamera()->getEye() + Vector3(-100, -100, -100),
			Vector3(10, 40, 10) , Vector3(0, 0, 0), 5, 2, Vector4{ 0,0,1,1 }, 1);
		break;
	}
	case 'G':
		//particula fuerza gravedad 1 masa 2
		systemparticle->generateParticle(4, GetCamera()->getEye() + Vector3(-40, -40, -40),
			Vector3(0, 30, 0), Vector3(0, 0, 0), 2, 15, Vector4{ 1,0,0,1 }, 2);
		break;
	case 'H':
		//particula fuerza gravedad 1 masa 20
		systemparticle->generateParticle(4, GetCamera()->getEye() + Vector3(-100, -50, -100)*3,
			Vector3(0, 20, 0), Vector3(0, 0, 0), 20, 15, Vector4{ 0.5,0,0,1 }, 5);
		break;
	case 'J':
		//particula fuerza gravedad 2
		systemparticle->generateParticle(5, GetCamera()->getEye() + Vector3(-100, -50, -100) ,
			Vector3(0, 100, 0), Vector3(0, 0, 0), 1, 30, Vector4{ 0,1,0,1 }, 3);
		break;
	case 'V':
		//particula fuerza viento 
		systemparticle->generateParticle(6, GetCamera()->getEye() + Vector3(-50, 0, -50),
			Vector3(5, 0, 0), Vector3(0, 0, 0), 2, 30, Vector4{ 0,0.5,0,1 }, 3);
		break;
	case 'B':
		//particula fuerza viento 
		systemparticle->generateParticle(9, GetCamera()->getEye() + Vector3(-50, 0, -50),
			Vector3(0, 0, 0), Vector3(0, 0, 0), 2, 30, Vector4{ 0,0.2,0,1 }, 4);

		break;
	case 'C':
		//particula fuerza WHIRL
		systemparticle->generateParticle(7, GetCamera()->getEye() + Vector3(-50, 0, -50),
			Vector3(0, 0, 0), Vector3(0, 0, 0), 2, 3000, Vector4{ 0.9,0.1,0.9,1 }, 2);
		break;
	case 'N':
		//particula expllosion
		systemparticle->generateParticle(8, Vector3(0, 2, 300), Vector3(0, 1, 0) * 80, Vector3(0, 0, 0), 0.02f, 30, Vector4{ 0.749, 0.749, 0.851, 1 }, 2.0f);
		break;
	case 'M':
		systemparticle->explosion();
		break;
	case '1':
		systemparticle->generateAnchoredSpring();
		break;
	case'2':
		systemparticle->generateSpring();
		break;
	case'+':
		systemparticle->morek();

	default:
		break;
	}
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
}


int main(int, const char* const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for (PxU32 i = 0; i < frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}