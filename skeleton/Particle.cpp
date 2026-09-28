#include "Particle.h"
#include "RenderUtils.hpp"
#include <iostream>
Particle::Particle(Vector3D pos, Vector3D pvel, Vector3D a, float d) : 
	pose(physx::PxTransform(physx::PxVec3(pos))), lastPose(pos), vel(pvel), acc(a), damping(d) {
	physx::PxShape* sphereShape = CreateShape(physx::PxSphereGeometry(1.0f));
	renderItem = new RenderItem(sphereShape, &pose, Vector4(1.0f, 0.0f, 0.0f, 1.0f));
};

Particle::~Particle() {
	if (renderItem) {
		renderItem->release();
		renderItem = nullptr;
	}
}

void Particle::integrateEuler(double t) {
	pose.p = pose.p + physx::PxVec3(vel) * t;
	vel = vel + acc * t;
	vel = vel * pow(damping, t); // para que el damping dependa del tiempo
}

void Particle::integrateSemiEuler(double t) {
	vel = vel + acc * t;
	vel = vel * pow(damping, t); // para que el damping dependa del tiempo
	pose.p = pose.p + physx::PxVec3(vel) * t;
}

void Particle::integrateVerlet(double t) {
	physx::PxVec3 last = pose.p;
	pose.p = 2 * pose.p - physx::PxVec3(lastPose) + physx::PxVec3(acc * t * t);
	lastPose = last;
}