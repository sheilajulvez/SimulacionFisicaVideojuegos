#include "GausianGeneratorParticle.h"
#include "FireWork.h"
GausianGeneratorParticle::GausianGeneratorParticle(Vector3 pos, Vector3 vel) {
	this->pos = pos;
	this->vel = vel;
}
GausianGeneratorParticle::~GausianGeneratorParticle() {

}
std::list<Particle*> GausianGeneratorParticle::generateParticles(int t) {
	list<Particle*> lista;
	

	switch (t)
	{
	case 1:
		for (int i = 0; i < _n_particles; i++) {
			// Genera posiciones y velocidades muestreadas de una distribución gaussiana 
			// u(mt) una función o un generador de números aleatorios
			Vector3 Vel = _mean_velocity + Vector3(_u(_mt) * vel.x, _u(_mt) * vel.y, _u(_mt) * vel.z);
			Vector3 Pos = _origin + Vector3(_u(_mt), _u(_mt), _u(_mt));
			float timer = distribution_a(_mt);
			float radio = abs(distribution_b(_mt));
			Vector4 color = (Vector4(distribution_c(_mt), distribution_c(_mt), distribution_c(_mt), 1));

			FireWork* fire = new FireWork(Pos, Vel, { 0,-9.8,0 }, 2, color, timer, 0, radio,0);
			lista.push_back(fire);
			fire->addGenerator(this);

		}

		return lista;
	case 2:
		
		for (int i = 0; i < 400; i++) {
			float time = 5;
			float radio = 0.1f; // Tamaño de las partículas (ajusta según lo necesites)
			Vector4 Col{ 1.0, 0, 0.0, 1 }; // Color de la estrella (amarillo)

			// Genera posiciones para la estrella de cinco puntas
			float angle = (2.0f * 3.14159f * i) / 100.0f;
			float radius = (i % 2 == 0) ? 0.5f : 1.0f; // Alterna entre dos radios para las puntas de la estrella
			float x = radius * cos(angle);
			float y = radius * sin(angle);
			float z = 0.0f; // Ubicación en el plano XY
			Vector3 Pos = _origin + Vector3(x, y, z);

			// Genera velocidades aleatorias
			Vector3 Vel{ distribution_a(_mt), distribution_a(_mt), distribution_a(_mt) }; // Velocidades aleatorias ajustadas

			lista.push_back(new FireWork(Pos, Vel, Vector3(0, -9.8, 0), 3, Col, time,  0, radio, 0));
		}
		return lista;
	case 10:

		for (int i = 0; i < 400; i++) {
			float time = 5;
			float radio = 0.1f; // Tamaño de las partículas (ajusta según lo necesites)
			Vector4 Col{ 0.0, 1.0, 0.0, 1 }; // Color de la estrella (amarillo)

			// Genera posiciones para la estrella de cinco puntas
			float angle = (2.0f * 3.14159f * i) / 100.0f;
			float radius = (i % 2 == 0) ? 0.5f : 1.0f; // Alterna entre dos radios para las puntas de la estrella
			float x = radius * cos(angle);
			float y = radius * sin(angle);
			float z = 0.0f; // Ubicación en el plano XY
			Vector3 Pos = _origin + Vector3(x, y, z);

			// Genera velocidades aleatorias
			Vector3 Vel{ distribution_a(_mt), distribution_a(_mt), distribution_a(_mt) }; // Velocidades aleatorias ajustadas

			lista.push_back(new FireWork(Pos, Vel, Vector3(0, -9.8, 0), 3, Col, time, 0, radio, 0));
		}
		return lista;
	default:
		break;
	}
}