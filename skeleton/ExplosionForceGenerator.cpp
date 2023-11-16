#include "ExplosionForceGenerator.h"
ExplosionForceGenerator::ExplosionForceGenerator(Vector3 inipos, Vector3 lado, float k, float tau) {
    this->inipos = inipos;
    this->lado = lado;
    this->k = k;
    this->tau = tau;
}
ExplosionForceGenerator::~ExplosionForceGenerator() {

}

void ExplosionForceGenerator::updateForce(Particle* p, double t) {

    Vector3 pos = p->getTrans().p;

    // Verificar si la part�cula est� dentro del cubo de explosi�n
    if ((pos.x >= inipos.x - lado.x * 0.5f && pos.x <= inipos.x + lado.x * 0.5f) &&
        (pos.y >= inipos.y - lado.y * 0.5f && pos.y <= inipos.y + lado.y * 0.5f) &&
        (pos.z >= inipos.z - lado.z * 0.5f && pos.z <= inipos.z + lado.z * 0.5f)) {
        // La part�cula est� dentro del cubo de explosi�n
        // Realiza las acciones que necesites para las part�culas dentro del cubo de explosi�n


        float r = calculateDistance(pos.x, pos.y, pos.z, inipos.x, inipos.y, inipos.z);
        float exponentialTerm = exp(-t / tau);
        Vector3 diff = pos - inipos;
        float magnitud_explosion = (k / (r * r)) * exponentialTerm;
        Vector3 forceDirection = pos - inipos;
        Vector3 explosionForce = magnitud_explosion * forceDirection;
        p->addForce(explosionForce);

    }





}
float ExplosionForceGenerator::calculateDistance(float x, float y, float z, float x_c, float y_c, float z_c) {
    float distance_squared = (x - x_c) * (x - x_c) + (y - y_c) * (y - y_c) + (z - z_c) * (z - z_c);
    float distance = sqrt(distance_squared);
    return distance;
}