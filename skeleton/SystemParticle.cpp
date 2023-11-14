#include "SystemParticle.h"
#include "SimpleGeneratorParticle.h"
#include"GausianGeneratorParticle.h"
SystemParticle::SystemParticle(const Vector3& g) {
	_gravity = g;
	_firework_generator = new SimpleGeneratorParticle(Vector3{ 50,50,50 }, Vector3{ 20,20,20 });
	_particle_generators.push_back(_firework_generator);
	_firework_generator = new GausianGeneratorParticle(Vector3{ 50,50,50 }, Vector3{ 20,20,20 });
	_particle_generators.push_back(_firework_generator);
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
			
			if (static_cast<FireWork*>(*it)->gettype() >=1) {
				std::list<Particle*> p = static_cast<FireWork*>(*it)->explode();
				for (auto d : p) {
					_particles.push_back(d);
				}
			}
			onParticleDeath(*it);
		}
		it = aux;
	}
}


// Method to generate a Firework with the appropiate type
void SystemParticle::generateParticle(unsigned firework_type, Vector3 pos, Vector3 vel, Vector3 acelera, int masa, float time, Vector4 color, int radio) {

	firework = new FireWork(pos, vel, acelera, masa, color, time, 0, radio, firework_type);
	_particles.push_back(firework);
	if (firework->gettype()==3)firework->addGenerator(_particle_generators.front());
	firework->addGenerator(_particle_generators.back());
	
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
