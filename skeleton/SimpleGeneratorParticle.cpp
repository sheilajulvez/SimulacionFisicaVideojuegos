#include "SimpleGeneratorParticle.h"
#include "FireWork.h"
SimpleGeneratorParticle::SimpleGeneratorParticle(Vector3 pos, Vector3 vel) {
	this->pos = pos;
	this->vel = vel;
	
}
SimpleGeneratorParticle:: ~SimpleGeneratorParticle(){}
list<Particle*> SimpleGeneratorParticle::generateParticles(int t) {
	std::list<Particle*> particles;

	switch (t)
	{
	case 3:
		
		for (int i = 0; i < _n_particles; i++) {
			
			Vector3 Vel = Vector3(0, distribucion_normal(_mt) * vel.y, 0);
			Vector3 Pos = _origin + Vector3(distribucion_normal(_mt) * pos.x, distribucion_normal(_mt) * pos.y, distribucion_normal(_mt) * pos.z);
			float time = distribucion_1_3(_mt);
			float radio = 0.4;
			Vector4 Col(0, 255, 0.91, 1);
			particles.push_back(new FireWork(Pos, Vel, Vector3(0, -9.8, 0), 3, Col, time, 0,radio,0));
		}

		return particles;
	default:
		break;
	}

}

