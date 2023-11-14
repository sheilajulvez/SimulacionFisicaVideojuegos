#pragma once
#include "PxPhysics.h"
#include "RenderUtils.hpp"
const float damping = 0.998;

class Particle
{
public:
	Particle(Vector3 Pos, Vector3 Vel, Vector3 acelera, int mas, Vector4 color, float timer, int payload, float radio);
	
	~Particle();
	void integrate(double t);//bool
	inline float gettimer() { return time; }
	inline void settimer(float t) {time = t;}
	inline bool getmuere() { return muere; }

	inline physx::PxTransform getTrans() { return trans; }
	inline void setPos(Vector3 newpos) { trans.p = newpos; }

	inline Vector3 getVel() {return vel;}
	inline void setVel(Vector3 vel) {	this->vel = vel;}

	inline Vector4 getColor() { return color; }
	inline void setColor(Vector4 color) {this->color = color; renderItem->color = color;}

	inline int getMasa() {
		return masa;
	}

	void addForce(Vector3 f);
	
	// Add force to apply in next integration only
	void clearForce();

protected:
	/*Posición inicial
		2. Velocidad inicial
		3. Tamaño inicial
		4. Color inicial
		5. Transparencia inicial
		6. Forma
		7. Tiempo de vida*/


	physx::PxTransform trans;
	Vector3 vel;
	float tam;
	Vector4 color;
	RenderItem* renderItem;
	float timer = 0;
	float time = 0;
	int payload = 0;
	bool muere;
	int masa;
	Vector3 acelera;

	// Accumulated force
	Vector3 force;
	
	
	


};




