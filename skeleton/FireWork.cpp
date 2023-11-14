#include "FireWork.h"
#include "GeneratorParticle.h"
FireWork::FireWork(Vector3 Pos, Vector3 Vel, Vector3 acelera, int mas, Vector4 color, float timer, int payload, float radio,int type):Particle(Pos,Vel,acelera,mas,color,timer,payload,radio) {
	_type = type;
}
FireWork::~FireWork() {

}
// The firework generates more fireworks when exploding --> they should be gathered by the System
std::list<Particle*> FireWork::explode() {
	_gens.front()->setOrigin(trans.p);	
	_gens.front()->setMeanVelocity(Vector3{ vel.x,0,vel.z });

	return _gens.front()->generateParticles(_type);
}
void FireWork::addGenerator(GeneratorParticle* p) {
	_gens.push_back(p);
}
//virtual Particle* clone() const