#include "SystemParticle.h"
#include "SimpleGeneratorParticle.h"
#include"GausianGeneratorParticle.h"
#include "GravityFocreGenerator.h"
#include "WindForceGenerator.h"
#include "WhirlwindForceGenerator.h"
#include "ExplosionForceGenerator.h"
SystemParticle::SystemParticle() {
	
	_firework_generator = new SimpleGeneratorParticle(Vector3{ 50,50,50 }, Vector3{ 20,20,20 });
	_particle_generators.push_back(_firework_generator);
	_firework_generator = new GausianGeneratorParticle(Vector3{ 50,50,50 }, Vector3{ 20,20,20 });
	_particle_generators.push_back(_firework_generator);

	//FORCE_GENERATOR[ gravity1, gravity2, wind, whirlwind, forceneerator,wind]
	force_generator = new GravityForceGenerator(g1);
	_force_generators.push_back(force_generator);
	force_generator = new GravityForceGenerator(g2);
	_force_generators.push_back(force_generator);
	force_generator = new WindForceGenerator(Vector3{ -300,0,0 }, Vector3{ -70,-70,-70 }, Vector3{ 100,100,100 }, 0.8, 0);
	_force_generators.push_back(force_generator);
	force_generator = new WhirlwindForceGenerator(Vector3{ 0.7f,0.03f,0.03f }, Vector3{ 10,0,0 }, Vector3{ 10,5,5 }, 2.0, 0);
	
	_force_generators.push_back(force_generator);
	force_generator = new ExplosionForceGenerator({ -50,-50,-50 }, { 90,90,90 }, 900, 1);
	_force_generators.push_back(force_generator);
	force_generator = new WindForceGenerator(Vector3{ 300,0,-300 }, Vector3{ -70,-70,-70 }, Vector3{ 100,100,100 }, 0.8, 0);
	_force_generators.push_back(force_generator);

	particleforceregistry = new ParticleForceRegistry();

}

SystemParticle::~SystemParticle(){

}
// Integrates the particles and checks for its lifetime, etc!
void SystemParticle:: update(double t) {
	//actualiza las particulas y las elimina en caso de que esten muertas

	list<Particle*>::iterator it = _particles.begin();
	while (it != _particles.end()) {
		auto aux = it;
		++aux;
		(*it)->integrate(t);
		if ((*it)->getmuere()) {
			
			if (static_cast<FireWork*>(*it)->gettype() ==1|| static_cast<FireWork*>(*it)->gettype() == 2|| static_cast<FireWork*>(*it)->gettype() == 3) {
				std::list<Particle*> p = static_cast<FireWork*>(*it)->explode();
				for (auto d : p) {
					_particles.push_back(d);
					//particleforceregistry->addRegistry(_force_generators.front(), d);
				}
			}
			onParticleDeath(*it);
		}
		it = aux;
	}
	particleforceregistry->updateForces(t);
}


// Method to generate a Firework with the appropiate type
void SystemParticle::generateParticle(unsigned firework_type, Vector3 pos, Vector3 vel, Vector3 acelera, int masa, float time, Vector4 color, int radio) {
	firework = new FireWork(pos, vel, acelera, masa, color, time, 0, radio, firework_type);
	switch (firework_type) {
	case 1:
		firework->addGenerator(_particle_generators.back());
		break;
	case 2:
		firework->addGenerator(_particle_generators.back());
		break;
	case 3:
		firework->addGenerator(_particle_generators.front());
		break;
	case 4:
		particleforceregistry->addRegistry(_force_generators[0], firework);
		break;
	case 5:
		particleforceregistry->addRegistry(_force_generators[1], firework);
		break;
	case 6:
		particleforceregistry->addRegistry(_force_generators[2], firework);
		particleforceregistry->addRegistry(_force_generators[0], firework);
		break;
	case 7:
		particleforceregistry->addRegistry(_force_generators[3], firework);
		particleforceregistry->addRegistry(_force_generators[0], firework);

		break;
	case 8:
	
		for (int i = 0; i < 15; ++i) {
			// Calcular una posición aleatoria dentro del área
			float randomRadius = (static_cast<float>(rand()) / RAND_MAX) * 50;
			float theta = (static_cast<float>(rand()) / RAND_MAX) * 2.0f * 3.14159f;
			float phi = (static_cast<float>(rand()) / RAND_MAX) * 2.0f * 3.14159f;
			float colora= (static_cast<float>(rand()) / RAND_MAX);
			float colorb = (static_cast<float>(rand()) / RAND_MAX);
			float colorc = (static_cast<float>(rand()) / RAND_MAX);

			float x = centre.x + randomRadius * sin(theta) * cos(phi);
			float y = centre.y - randomRadius * sin(theta) * sin(phi);
			float z = centre.z + randomRadius * cos(theta);

			// Dirección fija para mantenerse quietas
			Vector3 direction(0.0f, 0.0f, 0.0f);

			// Crear la partícula y añadirla al contenedor
			Particle* newParticle = new FireWork(Vector3(x, y, z), direction, _gravity, 2, Vector4{ 0.8, 0.2, 0, 1.0f }, 100, 0, 3, 1);
			_particles.push_back(newParticle);
			particles_explosion.push_back(newParticle);
		}
		break;
	case 9:
		particleforceregistry->addRegistry(_force_generators[5], firework);
		particleforceregistry->addRegistry(_force_generators[0], firework);
		break;
	default:
		break;

	}
	_particles.push_back(firework);
	
	
	
}



void SystemParticle::generateGenerator() {

}
// Gets a particle generator with name...
GeneratorParticle* SystemParticle::getParticleGenerator(const std::string& n) {
	return _firework_generator;
}

void SystemParticle::onParticleDeath(Particle* p) {
	_particles.remove(p);
	delete(p);
	
}
void SystemParticle::createFireworkSystem() {

}
void SystemParticle::explosion() {
	for (auto d : particles_explosion) {
		particleforceregistry->addRegistry(_force_generators[4], d);

	}

}
