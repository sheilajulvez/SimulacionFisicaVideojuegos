#include "SystemRigidBody.h"
SystemRigidBody::SystemRigidBody(SystemParticle* systemparticle) {
	this->systemparticle = systemparticle;
	registering = new RigidBodyForceRegistry();
	linearforcegenerator1 = new LinearForceGenerator();
	force_generators.push_back(linearforcegenerator1);
	linearforcegenerator2 = new LinearForceGenerator();
	force_generators.push_back(linearforcegenerator2);
	wind = new RigidBodyWindForceGenerator({ 0,0,0 }, { 0,0,0 }, { 1000,20,1000 },10,0);
	force_generators.push_back(wind);
	unavez = true;
	bloqueado = false;
}

SystemRigidBody::~SystemRigidBody() {

}

void SystemRigidBody::addRB(RigidBodyParticle* r) {
	particles.push_back(r);
}

void SystemRigidBody::update(double t) {

	auto it = particles.begin();
	while (!particles.empty() && it != particles.end()) {
		auto aux = it;
		++aux;

		(*it)->integrate(t);
		if ((*it)->getsoypelota() && unavez) {
			if ((*it)->getTrans().p.x > 200) {
				if (contadorvictoriasverde < 3) {
					systemparticle->generateParticle(3, Vector3(0, 150, 0),
						Vector3(0, 10, 0), Vector3(0, 0, 0), 5, 2, Vector4{ 0,1,0,1 }, 1);
					contadorvictoriasverde++;
					(*it)->dinamico()->setGlobalPose({ 0,10,0 });
					(*it)->dinamico()->setLinearVelocity({ 0,0,0 });
				}
				else {
					systemparticle->generateParticle(10, Vector3(0, 100, 0),
						Vector3(0, 1, 0) * 40, Vector3(0, 0, 0), 0.5f, 1, Vector4{ 0,1,0,1 }, 1);
					systemparticle->generateParticle(10, Vector3(-30, 100, 0),
						Vector3(0, 1, 0) * 40, Vector3(0, 0, 0), 0.5f, 1, Vector4{ 0,1,0,1 }, 1);
					systemparticle->generateParticle(10, Vector3(40, 100, 0),
						Vector3(0, 1, 0) * 40, Vector3(0, 0, 0), 0.5f, 1, Vector4{ 0,1,0,1 }, 1);
					systemparticle->generateParticle(10, Vector3(10, 100, 30),
						Vector3(0, 1, 0) * 40, Vector3(0, 0, 0), 0.5f, 1, Vector4{ 0,1,0,1 }, 1);
					systemparticle->generateParticle(10, Vector3(-10, 100, -30),
						Vector3(0, 1, 0) * 40, Vector3(0, 0, 0), 0.5f, 1, Vector4{ 0,1,0,1 }, 1);
					systemparticle->generateParticle(10, Vector3(20, 100, 20),
						Vector3(0, 1, 0) * 40, Vector3(0, 0, 0), 0.5f, 1, Vector4{ 0,1,0,1 }, 1);
					unavez = false;
				}



			}
			else if ((*it)->getTrans().p.x < -200) {
				if (contadorvictoriasrojo < 3) {
					systemparticle->generateParticle(11, Vector3(0, 150, 0),
						Vector3(0, 10, 0), Vector3(0, 0, 0), 5, 2, Vector4{ 1,0,0,1 }, 1);
					contadorvictoriasrojo++;
					(*it)->dinamico()->setGlobalPose({ 0,10,0 });
					(*it)->dinamico()->setLinearVelocity({ 0,0,0 });
				}
				else {
					systemparticle->generateParticle(2, Vector3(0, 100, 0),
						Vector3(0, 1, 0) * 40, Vector3(0, 0, 0), 0.5f, 1, Vector4{ 1,0,0,1 }, 1);
					systemparticle->generateParticle(2, Vector3(-30, 100, 0),
						Vector3(0, 1, 0) * 40, Vector3(0, 0, 0), 0.5f, 1, Vector4{ 1,0,0,1 }, 1);
					systemparticle->generateParticle(2, Vector3(40, 100, 0),
						Vector3(0, 1, 0) * 40, Vector3(0, 0, 0), 0.5f, 1, Vector4{ 1,0,0,1 }, 1);
					systemparticle->generateParticle(2, Vector3(10, 100, 30),
						Vector3(0, 1, 0) * 40, Vector3(0, 0, 0), 0.5f, 1, Vector4{ 1,0,0,1 }, 1);
					systemparticle->generateParticle(2, Vector3(-10, 100, -30),
						Vector3(0, 1, 0) * 40, Vector3(0, 0, 0), 0.5f, 1, Vector4{ 1,0,0,1 }, 1);
					systemparticle->generateParticle(2, Vector3(20, 100, 20),
						Vector3(0, 1, 0) * 40, Vector3(0, 0, 0), 0.5f, 1, Vector4{ 1,0,0,1 }, 1);
					unavez = false;
				}


			}
		}
		else if ((*it)->soydinamico() &&(*it)->dinamico()->getGlobalPose().p.x < -190)(*it)->dinamico()->setGlobalPose({ -190,10,(*it)->dinamico()->getGlobalPose().p.z });
		else if ((*it)->soydinamico()&&(*it)->dinamico()->getGlobalPose().p.x > 190)(*it)->dinamico()->setGlobalPose({ 190,10,(*it)->dinamico()->getGlobalPose().p.z });
		if (bloqueado) {
			tiempoActual = std::chrono::high_resolution_clock::now();
			std::chrono::milliseconds deltaTiempo = std::chrono::duration_cast<std::chrono::milliseconds>(tiempoActual - tiempoPrevio);
			double deltaTiempoSegundos = deltaTiempo.count() / 1000.0;	//segundos
			contadorTiempo += deltaTiempoSegundos;
			if (contadorTiempo > limite && (*it)->getsoypelota()) {
				registering->deleteRegistry(wind, (*it));
				tiempoPrevio = tiempoActual;
				// Esperar un breve periodo de tiempo antes de la próxima actualización
				tiempoActual = std::chrono::high_resolution_clock::now();
				contadorTiempo = 0;
				bloqueado = false;

			}
		}
		
		it = aux;
	}
	registering->updateForces(t);

	
}

void SystemRigidBody::addLinear1(RigidBodyParticle* p) {
	registering->addRegistry(linearforcegenerator1,p);

}
void SystemRigidBody::addLinear2(RigidBodyParticle* p) {
	registering->addRegistry(linearforcegenerator2, p);
}
void SystemRigidBody::añadirregistromuelle(RigidBodySprinngForceGenerator* s, RigidBodyParticle* p) {
	registering->addRegistry(s, p);
	force_generators.push_back(s);
}
void SystemRigidBody::añadirregistroviento(RigidBodyParticle* p) {
	if (!bloqueado) {
		wind->setf({ getrandom(),0,getrandom() });
		registering->addRegistry(wind, p);
		bloqueado = true;
	}
	
	
}
