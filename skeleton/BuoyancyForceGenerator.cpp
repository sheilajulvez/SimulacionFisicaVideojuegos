#include "BuoyancyForceGenerator.h"
BuoyancyForceGenerator::BuoyancyForceGenerator(float h, float V, float d, const Vector3& pos) :  height(h),volume(V), liquid_density(d), trans(pos){
	
	renderItem = new RenderItem(CreateShape(physx::PxBoxGeometry(Vector3{h,5,h})), &trans, {0.4,0.3,0.9,0.5});
}
BuoyancyForceGenerator::~BuoyancyForceGenerator() {

}
void BuoyancyForceGenerator::updateForce(Particle* particle, double t) {
	float h = particle->getTrans().p.y;
	float h0 = trans.p.y;

	Vector3 f(0, 0, 0);
	float immersed = 0.0;
	if (h - h0 > height * 0.5) {
		immersed = 0.0;
	}
	else if (h0 - h > height * 0.5) {
		immersed = 1.0;
	}
	else {
		immersed = (h0 - h) / height + 0.5;
	}
	f.y = liquid_density* volume* immersed*9.8;
	particle->addForce(f);
}