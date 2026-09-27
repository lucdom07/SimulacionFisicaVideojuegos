#include "Particle.h"
#include "RenderUtils.hpp"
Particle::Particle(Vector3D pos, Vector3D pvel, Vector3D a) : pose(physx::PxTransform(physx::PxVec3(pos))), vel(pvel), acc(a) {
	physx::PxShape* sphereShape = CreateShape(physx::PxSphereGeometry(1.0f));
	renderItem = new RenderItem(sphereShape, &pose, Vector4(1.0f, 0.0f, 0.0f, 1.0f));
};

Particle::~Particle() {
	if (renderItem) {
		renderItem->release();
		renderItem = nullptr;
	}
}

void Particle::integrate(double t) {
	pose.p = pose.p + physx::PxVec3(vel) * t;
	vel = vel + acc * t;
}