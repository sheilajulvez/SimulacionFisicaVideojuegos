#pragma once
#include "Particle.h"
#include <list>
class GeneratorParticle;
class FireWork:public Particle
{
public:
	FireWork(Vector3 pos, Vector3 vel, Vector3 aceler, int mas, Vector4 color, float timer, int payload, float radio, int type);
	virtual ~FireWork();
	// The firework generates more fireworks when exploding --> they should be gathered by the System
	std::list<Particle*> explode();
	void addGenerator(GeneratorParticle* p);
	//virtual Particle* clone() const
	unsigned inline gettype() { return _type; }
protected:
	bool isfirework;
	// Type
	unsigned _type;
	std::list<GeneratorParticle*> _gens;

};

