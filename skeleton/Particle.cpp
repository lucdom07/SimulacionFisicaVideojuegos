#include <iostream>
#include "Particle.h"
#include "RenderUtils.hpp"

Particle::Particle() : active(false), pose(physx::PxTransform(physx::PxVec3(Vector3D(0,0,0)))), lastPose(Vector3D(0, 0, 0)), 
	vel(Vector3D(0, 0, 0)), acc(Vector3D(0, 0, 0)), mass(0.f), gravity(Vector3D(0, 0, 0)), lifeTime(0), lTimer(0) {
	physx::PxShape* sphereShape = CreateShape(physx::PxSphereGeometry(0.1f));
	renderItem = new RenderItem(sphereShape, &pose, Vector4(0.f, 0.f, 0.f, 0.f));
};

Particle::Particle(Vector3D pos, Vector3D pvel, Vector3D a, Vector3D color, float m, float g, float life, float size) :
	active(true), pose(physx::PxTransform(physx::PxVec3(pos))), lastPose(pos), vel(pvel), acc(a), 
	mass(m), gravity(Vector3D(0, -g, 0)), lifeTime(life), lTimer(0) {
	physx::PxShape* sphereShape = CreateShape(physx::PxSphereGeometry(size));
	renderItem = new RenderItem(sphereShape, &pose, Vector4(color.x, color.y, color.z, 1.0f));
};

Particle::~Particle() {
	if (renderItem) {
		renderItem->release();
		renderItem = nullptr;
	}
}

void Particle::configParticle(Vector3D pos, Vector3D pvel, Vector3D a, Vector3D color, float m, float g, float life, float size) {
	pose = physx::PxTransform(physx::PxVec3(pos));
	lastPose = pos;
	vel = pvel; 
	acc = a;
	mass = m; 
	gravity = Vector3D(0, -g, 0); 
	lifeTime = life; 
	lTimer = 0;

	if (renderItem) delete renderItem;
	physx::PxShape* sphereShape = CreateShape(physx::PxSphereGeometry(size));
	renderItem = new RenderItem(sphereShape, &pose, Vector4(color.x, color.y, color.z, 1.0f));
}

void Particle::integrateEuler(double t) {
	pose.p = pose.p + physx::PxVec3(vel) * t;
	vel = vel + acc * t;
	vel = vel * pow(damping, t); // para que el damping dependa del tiempo
}

void Particle::integrateSemiEuler(double t) {
	if (!active) return;
	vel = vel + gravity * mass * t;
	vel = vel * pow(damping, t);
	pose.p = pose.p + physx::PxVec3(vel * t + gravity * mass * 0.5f * t * t);
}

void Particle::integrateVerlet(double t) {
	physx::PxVec3 last = pose.p;
	pose.p = 2 * pose.p - physx::PxVec3(lastPose) + physx::PxVec3(acc * t * t);
	lastPose = last;
}

void Particle::changeMass(bool increase) {
	(increase) ? mass += massMod : mass -= massMod;
}

void Particle::changeGravity(bool increase) {
	(increase) ? gravity -= Vector3D(0, gravMod, 0) : gravity += Vector3D(0, gravMod, 0);
}

void Particle::countLifeTime(double t) {
	if (!active) return;
	lTimer += t;
	if (lTimer >= lifeTime) active = false;
}

void Particle::decreaseOpacity(double t) {
	if (!active) return;
	renderItem->color.w -= opacMod * (t/lifeTime);
}

void Particle::decreaseSize(double t) {
	if (!active) return;
	float newSize = renderItem->shape->getGeometry().sphere().radius - (sizeMod * (t / lifeTime));
	Vector4 currColor = renderItem->color;
	if (renderItem) delete renderItem;
	physx::PxShape* sphereShape = CreateShape(physx::PxSphereGeometry(newSize));
	renderItem = new RenderItem(sphereShape, &pose, currColor);
}