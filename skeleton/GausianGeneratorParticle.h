#pragma once
#include "GeneratorParticle.h"
class GausianGeneratorParticle:public GeneratorParticle
{
public:
	GausianGeneratorParticle(Vector3 pos, Vector3 vel);
	~GausianGeneratorParticle();
	std::list<Particle*> generateParticles(int type);
private:
	Vector3 pos, vel;
	//se utilizan para generar números aleatorios que siguen las distribuciones normales especificadas
	normal_distribution<float> distribution_a{ 1, 3 };
	normal_distribution<float> distribution_b{ 0.6, 0.7 };
	normal_distribution<float> distribution_c{ 0.5, 0.5 };

};


