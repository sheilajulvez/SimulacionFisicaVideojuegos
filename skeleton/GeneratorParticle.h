#pragma once
#include <list>
#include <random>
#include "Particle.h"

using namespace std;
class GeneratorParticle {
public:
	
	inline void setOrigin(const Vector3& p) { _origin = p; }
	inline void setMeanVelocity(const Vector3& v) {_mean_velocity= v;}
	inline Vector3 getMeanVelocity() const {return _mean_velocity;}
	inline void setMeanDuration(double new_duration) { _model_particle->settimer(new_duration);}
	inline void setNParticles(int n_p) { _n_particles = n_p; }

	//! @brief --> sets the particle, including its type, lifetime and mean positions and velocities
	inline void setParticle(Particle* p, bool modify_pos_vel =true) {
		delete _model_particle;
		//_model_particle = p->clone();
		if (modify_pos_vel) {
			_origin = p->getTrans().p;	//COMENTADO
			_mean_velocity = p->getVel();
		}
		_model_particle->setPos({ -1000.0f, -1000.0f, -1000.0f });
	}
	
	virtual std::list<Particle*> generateParticles(int type) = 0;
protected:
	int _n_particles = 100; // Number of particles for each generateParticles call(TODO: add randomness ? ? )
	double _generation_prob = 0.2; // IF 1.0 --> always produces particles COMENTADO cambiar a 0.2
	Particle* _model_particle = nullptr; // Has the attributes of the particle that will be generated!(damping, lifetime, etc.)
	Vector3 _origin, _mean_velocity;
	mt19937 _mt;	//Random EL INCLUDE <RANDOM>
	uniform_real_distribution<double> _u{ 0,1 };
	std::string _name;
};



