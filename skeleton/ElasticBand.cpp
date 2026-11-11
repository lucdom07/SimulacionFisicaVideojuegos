#include "ElasticBand.h"
#include <iostream>

ElasticBand::ElasticBand(double k, double rLength, Particle* other) : SpringGenerator(k, rLength, other) {

}

void ElasticBand::updateForce(Particle* particle, float dt) {
	Vector3D relPos = mOther->getPos() - particle->getPos();
	Vector3D force;

	const float length = relPos.magnitude();

	// si el muelle se encoje, no se le aplica la fuerza
	if (length <= mRestLength) return;
	const float deltaX = length - mRestLength;

	force = relPos.normalize() * deltaX * mK;

	particle->acumulateForce(force);
}