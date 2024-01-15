#include <ctype.h>
#include <PxPhysicsAPI.h>
#include <vector>
#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"
#include <iostream>
#include <list>
#include "SystemParticle.h"
#include "SystemRigidBody.h"
#include "RigidBodyForceRegistry.h"
#include "RigidBodyParticle.h"
#include "RigidBodySprinngForceGenerator.h"

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
SystemRigidBody* systemRigidBody = nullptr;

using namespace std;
//std::vector<Particle*> particulas;
// Initialize physics engine
RigidBodyParticle* player1;
RigidBodyParticle* player2;
RigidBodyParticle* pelota;
RigidBodyParticle* porteria1;
RigidBodyParticle* cuadrado;
RigidBodyParticle* porteria2;
RigidBodyParticle* cuadrado2;
RigidBodySprinngForceGenerator* spring1;
RigidBodySprinngForceGenerator* spring2;

void PrimerJugador() {
	
	PxRigidDynamic* new_solid = gPhysics->createRigidDynamic(PxTransform({ -100,10,0 }));
	new_solid->setLinearVelocity({ 0,0,0 });
	new_solid->setAngularVelocity({ 0,0,0 });
	PxShape* shape_ad = CreateShape(PxCapsuleGeometry(8,5));
	new_solid->attachShape(*shape_ad);
	PxRigidBodyExt::updateMassAndInertia(*new_solid, 0.15);
	gScene->addActor(*new_solid);

	//pintarlo
	RenderItem* dynamic_item = new RenderItem(shape_ad, new_solid, {0,1,0,1 });
	player1 = new RigidBodyParticle(gPhysics, gScene, dynamic_item, new_solid);

	systemRigidBody->addRB(player1);
	systemRigidBody->addLinear1(player1);
}
void SegundoJugador() {

	PxRigidDynamic* new_solid = gPhysics->createRigidDynamic(PxTransform({ 100,10,0 }));
	new_solid->setLinearVelocity({ 0,0,0 });
	new_solid->setAngularVelocity({ 0,0,0 });
	PxShape* shape_ad = CreateShape(PxCapsuleGeometry(8, 5));
	new_solid->attachShape(*shape_ad);
	PxRigidBodyExt::updateMassAndInertia(*new_solid, 0.15);
	gScene->addActor(*new_solid);

	//pintarlo
	RenderItem* dynamic_item = new RenderItem(shape_ad, new_solid, {1,0,0,1 });
	player2 = new RigidBodyParticle(gPhysics, gScene, dynamic_item, new_solid);

	systemRigidBody->addRB(player2);
	systemRigidBody->addLinear2(player2);

}
void Pelota() {
	PxRigidDynamic* new_solid = gPhysics->createRigidDynamic(PxTransform({ GetCamera()->getEye().x,10, GetCamera()->getEye().z }));
	new_solid->setLinearVelocity({ 0,0,0 });
	new_solid->setAngularVelocity({ 0,0,0 });
	PxShape* shape_ad = CreateShape(PxSphereGeometry(5));
	new_solid->attachShape(*shape_ad);
	PxRigidBodyExt::updateMassAndInertia(*new_solid, 0.15);
	gScene->addActor(*new_solid);

	//pintarlo
	RenderItem* dynamic_item = new RenderItem(shape_ad, new_solid, { 0,0,1,1 });
	pelota=new RigidBodyParticle(gPhysics, gScene, dynamic_item, new_solid);
	pelota->setpelota();
	systemRigidBody->addRB(pelota);
	

}
void PorteriasA() {
	PxRigidDynamic* parte1 = gPhysics->createRigidDynamic(PxTransform({ 200,0,50 }));
	parte1->setLinearVelocity({ 0,0,0 });
	parte1->setAngularVelocity({ 0,0,0 });
	PxShape* shape = CreateShape(PxBoxGeometry(3, 50, 3));
	parte1->attachShape(*shape);
	PxRigidBodyExt::updateMassAndInertia(*parte1, 0.15);
	gScene->addActor(*parte1);
	RenderItem* item= new RenderItem(shape, parte1, { 1,0,0,1 });
	 porteria1= new RigidBodyParticle(gPhysics, gScene, item, parte1);
	systemRigidBody->addRB(porteria1);

	/*PxRigidDynamic* parte2 = gPhysics->createRigidDynamic(PxTransform({ 200,0,-30 }));
	parte2->setLinearVelocity({ 0,0,0 });
	parte2->setAngularVelocity({ 0,0,0 });
	PxShape* shape2 = CreateShape(PxBoxGeometry(3, 100, 3));
	parte2->attachShape(*shape2);
	PxRigidBodyExt::updateMassAndInertia(*parte1, 0.15);
	gScene->addActor(*parte2);
	RenderItem* item2=new RenderItem(shape, parte2, { 1,0,0,1 });
	RigidBodyParticle* p2 = new RigidBodyParticle(gPhysics, gScene, item2, parte2);
	systemRigidBody->addRB(p2);*/

	
	
	//RigidBodySprinngForceGenerator* spring2 = new RigidBodySprinngForceGenerator(1, -20, p2, { 200,0,50 });
	
	

}
void PorteriasB() {
	/*PxRigidStatic* parte1 = gPhysics->createRigidStatic(PxTransform({ -200,0,50 }));
	PxShape* shape = CreateShape(PxBoxGeometry(3, 100, 3));
	parte1->attachShape(*shape);
	gScene->addActor(*parte1);
	RenderItem* item = new RenderItem(shape, parte1, { 0,1,0,1 });

	PxRigidStatic* parte2 = gPhysics->createRigidStatic(PxTransform({ -200,0,-30 }));
	PxShape* shape2 = CreateShape(PxBoxGeometry(3, 50, 3));
	parte2->attachShape(*shape2);
	gScene->addActor(*parte2);
	RenderItem* item2 = new RenderItem(shape, parte2, { 0,1,0,1 });*/
	PxRigidDynamic* parte2 = gPhysics->createRigidDynamic(PxTransform({ -200,0,50 }));
	parte2->setLinearVelocity({ 0,0,0 });
	parte2->setAngularVelocity({ 0,0,0 });
	PxShape* shape = CreateShape(PxBoxGeometry(3, 50, 3));
	parte2->attachShape(*shape);
	PxRigidBodyExt::updateMassAndInertia(*parte2, 0.15);
	gScene->addActor(*parte2);
	RenderItem* item = new RenderItem(shape, parte2, { 0,1,0,1 });
	porteria2 = new RigidBodyParticle(gPhysics, gScene, item, parte2);
	systemRigidBody->addRB(porteria2);

}
void Bordes() {
	PxRigidStatic* parte1 = gPhysics->createRigidStatic(PxTransform({ -200,0,150 }));
	PxShape* shape = CreateShape(PxBoxGeometry(3, 20, 100));
	parte1->attachShape(*shape);
	gScene->addActor(*parte1);
	RenderItem* item = new RenderItem(shape, parte1, { 0.25,0,0.5,1 });
	cuadrado2 = new RigidBodyParticle(gPhysics, gScene, item, parte1);
	systemRigidBody->addRB(cuadrado2);
	spring2 = new RigidBodySprinngForceGenerator(1, 0, cuadrado2, { -200,0,50 });

	PxRigidStatic* parte2 = gPhysics->createRigidStatic(PxTransform({ 0,0,160 }));
	PxShape* shape2 = CreateShape(PxBoxGeometry(300, 20, 10));
	parte2->attachShape(*shape2);
	gScene->addActor(*parte2);
	RenderItem* item2 = new RenderItem(shape2, parte2, { 0.25,0,0.5,1 });

	PxRigidStatic* parte3= gPhysics->createRigidStatic(PxTransform({ 0,0,-100 }));
	PxShape* shape3 = CreateShape(PxBoxGeometry(300, 20, 10));
	parte3->attachShape(*shape3);
	gScene->addActor(*parte3);
	RenderItem* item3= new RenderItem(shape3, parte3, { 0.25,0,0.5,1 });

	PxRigidStatic* parte5 = gPhysics->createRigidStatic(PxTransform({ -200,0,-130 }));
	PxShape* shape5 = CreateShape(PxBoxGeometry(3, 20, 100));
	parte5->attachShape(*shape5);
	gScene->addActor(*parte5);
	RenderItem* item5 = new RenderItem(shape5, parte5, { 0.25,0,0.5,1 });
	

	PxRigidStatic* parte6 = gPhysics->createRigidStatic(PxTransform({ 200,0,-130 }));
	PxShape* shape6 = CreateShape(PxBoxGeometry(3, 20, 100));
	parte6->attachShape(*shape6);
	gScene->addActor(*parte6);
	RenderItem* item6 = new RenderItem(shape6, parte6, { 0.25,0,0.5,1 });
	cuadrado = new RigidBodyParticle(gPhysics, gScene, item6, parte6);
	systemRigidBody->addRB(cuadrado);
	spring1 = new RigidBodySprinngForceGenerator(1, 0, cuadrado, { 200,0,50 });

	PxRigidStatic* parte7 = gPhysics->createRigidStatic(PxTransform({ 200,0,150 }));
	PxShape* shape7 = CreateShape(PxBoxGeometry(3, 20, 100));
	parte7->attachShape(*shape7);
	gScene->addActor(*parte7);
	RenderItem* item7 = new RenderItem(shape7, parte7, { 0.25,0,0.5,1 });
}
void CreaScene() {

	PxRigidStatic* suelo = gPhysics->createRigidStatic(PxTransform({ 0,0,0 }));
	PxShape* shape = CreateShape(PxBoxGeometry(400, 0.9, 400));
	suelo->attachShape(*shape);
	//loañade a la escena
	gScene->addActor(*suelo);
	//renderizado
	RenderItem* item;
	item = new RenderItem(shape, suelo, { 0.8,0.8,0.8,1 });
	
	PorteriasA(); PorteriasB();
	Bordes();
	PrimerJugador();
	SegundoJugador();
	Pelota();
	systemRigidBody->añadirregistromuelle(spring1, porteria1);
	systemRigidBody->añadirregistromuelle(spring2, porteria2);

}
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
	systemRigidBody = new SystemRigidBody(systemparticle);
	CreaScene();

}

// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds

// Function to clean data
// Add custom code to the begining of the function

void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);

	gScene->simulate(t);
	gScene->fetchResults(true);
	systemparticle->update(t);
	systemRigidBody->update(t);
	GetCamera()->setPosition(pelota->dinamico()->getGlobalPose().p.x, pelota->dinamico()->getGlobalPose().p.z);
	
}
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
	//case 'B': {
	//	//Particula generador gausiana distribucion 1
 //	  systemparticle->generateParticle(1, GetCamera()->getEye() + Vector3(-100, -100, -100), 
	//		Vector3(0, 10, 0) , Vector3(0, 9.8, 0), 2, 3, Vector4{ 0.749,0.800,0,1 }, 4);
	//	break;
	//}
	//case 'N': {
	//	//Particula generador gausiano distribucion 2
	//	systemparticle->generateParticle(2, GetCamera()->getEye()+Vector3(-40,-40,-40),
	//		Vector3(0, 1, 0) * 40, Vector3(0, 0, 0), 0.5f, 1, Vector4{ 1,0,0,1 }, 1);
	//	break;
	//}
	//case 'M':
	//{	//Particula generador simple 
	//	systemparticle->generateParticle(3, GetCamera()->getEye() + Vector3(-100, -100, -100),
	//		Vector3(10, 40, 10) , Vector3(0, 0, 0), 5, 2, Vector4{ 0,0,1,1 }, 1);
	//	break;
	//}
	//case 'G':
	//	//particula fuerza gravedad 1 masa 2
	//	systemparticle->generateParticle(4, GetCamera()->getEye() + Vector3(-40, -40, -40),
	//		Vector3(0, 30, 0), Vector3(0, 0, 0), 2, 15, Vector4{ 1,0,0,1 }, 2);
	//	break;
	//case 'H':
	//	//particula fuerza gravedad 1 masa 20
	//	systemparticle->generateParticle(4, GetCamera()->getEye() + Vector3(-100, -50, -100)*3,
	//		Vector3(0, 20, 0), Vector3(0, 0, 0), 20, 15, Vector4{ 0.5,0,0,1 }, 5);
	//	break;
	//case 'J':
	//	//particula fuerza gravedad 2
	//	systemparticle->generateParticle(5, GetCamera()->getEye() + Vector3(-100, -50, -100) ,
	//		Vector3(0, 100, 0), Vector3(0, 0, 0), 1, 30, Vector4{ 0,1,0,1 }, 3);
	//	break;
	//case 'V':
	//	//particula fuerza viento 
	//	systemparticle->generateParticle(6, GetCamera()->getEye() + Vector3(-50, 0, -50),
	//		Vector3(5, 0, 0), Vector3(0, 0, 0), 2, 30, Vector4{ 0,0.5,0,1 }, 3);
	//	break;
	//case 'B':
	//	//particula fuerza viento 
	//	systemparticle->generateParticle(9, GetCamera()->getEye() + Vector3(-50, 0, -50),
	//		Vector3(0, 0, 0), Vector3(0, 0, 0), 2, 30, Vector4{ 0,0.2,0,1 }, 4);

	//	break;
	//case 'C':
	//	//particula fuerza WHIRL
	//	systemparticle->generateParticle(7, GetCamera()->getEye() + Vector3(-50, 0, -50),
	//		Vector3(0, 0, 0), Vector3(0, 0, 0), 2, 3000, Vector4{ 0.9,0.1,0.9,1 }, 2);
	//	break;
	//case 'N':
	//	//particula expllosion
	//	systemparticle->generateParticle(8, Vector3(0, 2, 300), Vector3(0, 1, 0) * 80, Vector3(0, 0, 0), 0.02f, 30, Vector4{ 0.749, 0.749, 0.851, 1 }, 2.0f);
	//	break;
	//case 'M':
	//	systemparticle->explosion();
	//	break;
	//case '1':
	//	systemparticle->generateAnchoredSpring();
	//	break;
	//case'2':
	//	systemparticle->generateSpring();
	//	break;
	//case'+':
	//	systemparticle->morek();
	//	break;
	//case'3':
	//	systemparticle->generateBuoyancySpring();
	//	break;
	case 'L':
		systemRigidBody->getforcelinear1()->setdir({ -100,0,0 });
		break;
	
	case'J':
		systemRigidBody->getforcelinear1()->setdir({ 100,0,0 });
		break;
	case'I':
		systemRigidBody->getforcelinear1()->setdir({ 0,0,100 });
		break;
	case'K':
		systemRigidBody->getforcelinear1()->setdir({ 0,0,-100 });
		break;
	case 'H':
		systemRigidBody->getforcelinear2()->setdir({ -100,0,0 });
		break;
	case'F':
		systemRigidBody->getforcelinear2()->setdir({ 100,0,0 });
		break;
	case'T':
		systemRigidBody->getforcelinear2()->setdir({ 0,0,100 });
		break;
	case'G':
		systemRigidBody->getforcelinear2()->setdir({ 0,0,-100 });
		break;
	case' ': 
		
		systemRigidBody->añadirregistroviento(pelota);
		break;

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