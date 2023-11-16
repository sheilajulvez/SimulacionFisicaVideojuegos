#pragma once

#include "GeneratorParticle.h"
#include "ForceGenerator.h"
#include "ParticleForceRegistry.h"
#include "FireWork.h"
class SystemParticle
{
public :
	// Creates a void system with a det. gravity
		SystemParticle();	//COMENTADO -3.8
		virtual ~SystemParticle();
		// Integrates the particles and checks for its lifetime, etc!
		void update(double t);
		// Method to generate a Firework with the appropiate type
		void generateParticle(unsigned firework_type, Vector3 pos, Vector3 vel, Vector3 acelera, int masa, float time, Vector4 color, int radio);
		void generateGenerator();
		// Gets a particle generator with name...
		GeneratorParticle* getParticleGenerator(const std::string& n);

		void explosion();
protected:
	std::list <Particle*> _particles;
	std::list <GeneratorParticle*> _particle_generators; // These are the registred generators(for on demand set generation prob.to 0
	std::vector<ForceGenerator*> _force_generators;
	std::list<Particle*> particles_explosion;
	FireWork* firework;
	ParticleForceRegistry* particleforceregistry;
	
	
	GeneratorParticle* _firework_generator; // This generator is only to shoot the firework!!
	ForceGenerator* force_generator;
	Vector3 _gravity;
	//std::vector<Firework*> _firework_pool; // Fireworks to be used as models!
	//! This is used currently in the Fireworks to spread more Fireworks!
	void onParticleDeath(Particle* p);
	void createFireworkSystem();
	Vector3 g1 = { 0.0f, -3.8f, 0.0f };
	Vector3 g2 = { 0.0f, -100.8f, 0.0f };
	Vector3 centre{ -50, -30, -50} ;
	
};

 
