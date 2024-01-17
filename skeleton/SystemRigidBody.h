#include "RenderUtils.hpp"
#include "RigidBodyParticle.h"
#include <list>
#include "RigidBodyForceRegistry.h"
#include "RigidBodyForceGenerator.h"
#include "SystemParticle.h"
#include "LinearForceGenerator.h"
#include "RigidBodySprinngForceGenerator.h"
#include "RigidBodyWindForceGenerator.h"
#include <random>
#include <chrono>
using namespace physx;
using namespace std;

class SystemRigidBody {
private:
	RigidBodyForceRegistry* registering;	//el registro
	std::list<RigidBodyParticle*> particles;//lista con particulas
	std::vector<RigidBodyForceGenerator*> force_generators;
	LinearForceGenerator* linearforcegenerator1;
	LinearForceGenerator* linearforcegenerator2;
	RigidBodyWindForceGenerator* wind;
	
	SystemParticle* systemparticle;
	bool unavez, bloqueado;
	// Inicializar el tiempo actual y el tiempo previo
	std::chrono::high_resolution_clock::time_point tiempoPrevio = std::chrono::high_resolution_clock::now();
	std::chrono::high_resolution_clock::time_point tiempoActual = std::chrono::high_resolution_clock::now();

	// Inicializar el contador de tiempo en segundos
	double contadorTiempo = 0.0;
	int limite = 5;
	bool fin = false;
	int contadorvictoriasrojo = 0;
	int contadorvictoriasverde = 0;


	
public:
	SystemRigidBody(SystemParticle* systemparticle);
	~SystemRigidBody();
	void addRB(RigidBodyParticle* r);
	void update(double t);
	void addLinear1(RigidBodyParticle* p);
	void addLinear2(RigidBodyParticle* p);
	inline  LinearForceGenerator* getforcelinear1() { return static_cast<LinearForceGenerator*> (force_generators[0]); };
	inline  LinearForceGenerator* getforcelinear2() { return static_cast<LinearForceGenerator*> (force_generators[1]); };
	void añadirregistromuelle(RigidBodySprinngForceGenerator* s, RigidBodyParticle* p);
	void añadirregistroviento(RigidBodyParticle* p);
	inline  float getrandom(){
		std::random_device rd;  // Obtener una semilla de hardware (si está disponible)
		std::mt19937 gen(rd());  // Inicializar el generador con la semilla

		// Definir la distribución que quieres (por ejemplo, de 1 a 100)
		std::uniform_int_distribution<> distribution(-50, 50);

		// Generar un número aleatorio
		float randomNumber = distribution(gen);
		return randomNumber;
	}
	inline bool getfin() { return fin; }
};