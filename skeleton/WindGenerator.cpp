#include "WindGenerator.h"

WindGenerator::WindGenerator(Vector3D dimArea, Vector3D pos, Vector3D vel, float wk1, float wk2) : 
	windTrans(Vector3(pos)), windVel(vel), k1(wk1), k2(wk2) {
	physx::PxShape* shape = CreateShape(physx::PxBoxGeometry(Vector3(dimArea)));
	renderItem = new RenderItem(shape, &windTrans, Vector4(0.f, 0.f, 0.f, 0.f));
}

WindGenerator::~WindGenerator() {
	if (renderItem) renderItem->release();
}

void WindGenerator::updateForce(Particle* particle, float dt) {
	// Si la partícula no está en el área del viento, no se aplica la fuerza
	if (!renderItem->checkCollision(particle->getRendeItem())) return;

	Vector3D windForce = (windVel - particle->getVel()) * k1 + (windVel - particle->getVel()) * (windVel - particle->getVel()).magnitude() * k2;
	particle->acumulateForce(windForce);
}