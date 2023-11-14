#pragma once
#include "GeneratorParticle.h"
class SimpleGeneratorParticle: public GeneratorParticle
{
public:
public:
	
	

	SimpleGeneratorParticle(Vector3 pos, Vector3 vel);
	virtual ~SimpleGeneratorParticle();
	std::list<Particle*> generateParticles(int type) override;//COMENTADO quizas recibe el type;
	//list<Particle*> generatefirework1();//DESCOMENTAR;
protected:
	Vector3 pos, vel;

	std::uniform_real_distribution<float> distribucion_normal{ 0, 1 }; //Normalizada
	std::uniform_real_distribution<float> distribucion_1_3{ 1, 3 };
	
};

