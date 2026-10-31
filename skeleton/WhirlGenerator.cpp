#include "WhirlGenerator.h"

void WhirlGenerator::updateForce(Particle* particle, float dt) {
	// Si la partícula no está en el área del torbellino, no se aplica la fuerza
	if (!renderItem->checkCollision(particle->getRendeItem())) return;

	Vector3 partPos = particle->getPos();
	windVel = Vector3D(partPos.x - windTrans.p.x, 50.f - (partPos.y - windTrans.p.y), -(partPos.z - windTrans.p.z)) * k1;

	Vector3D windForce = (windVel - particle->getVel()) * k1 + (windVel - particle->getVel()) * (windVel - particle->getVel()).magnitude() * k2;
	particle->acumulateForce(windForce);
}