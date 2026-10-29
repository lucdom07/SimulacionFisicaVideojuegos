#include <iostream>
#include "Particle.h"
#include "RenderUtils.hpp"

Particle::Particle() : active(false), pose(physx::PxTransform(physx::PxVec3(Vector3D(0,0,0)))), lastPose(Vector3D(0, 0, 0)), 
	vel(Vector3D(0, 0, 0)), acc(Vector3D(0,0,0)), f(Vector3D()), mass(0.f), invMass(0.f), lifeTime(0), lTimer(0), initSize(0.f) {
	physx::PxShape* sphereShape = CreateShape(physx::PxSphereGeometry(0.0001f));
	renderItem = new RenderItem(sphereShape, &pose, Vector4(0.f, 0.f, 0.f, 0.f));
};

Particle::Particle(Vector3D pos, Vector3D pvel, Vector3D color, float m, float life, float size) :
	active(true), pose(physx::PxTransform(physx::PxVec3(pos))), lastPose(pos), vel(pvel), acc(Vector3D(0, 0, 0)), mass(m), invMass(1/m), f(Vector3D()),
	lifeTime(life), lTimer(0), initSize(size) {
	physx::PxShape* sphereShape = CreateShape(physx::PxSphereGeometry(size));
	renderItem = new RenderItem(sphereShape, &pose, Vector4(color.x, color.y, color.z, 1.0f));
};

Particle::~Particle() {
	if (renderItem) {
		renderItem->release();
		renderItem = nullptr;
	}
}

void Particle::update(double dt) {
	countLifeTime(dt);
	decreaseOpacity(dt);
	decreaseSize(dt);
}

void Particle::cleanAcumulator() {
	f = Vector3D();
}

void Particle::acumulateForce(Vector3D F) {
	f += F;
}

void Particle::configParticle(Vector3D pos, Vector3D pvel, Vector3D color, float m, float life, float size) {
	pose = physx::PxTransform(physx::PxVec3(pos));
	acc = Vector3D(0, 0, 0);
	lastPose = pos;
	vel = pvel; 
	initSize = size;
	lifeTime = life; 
	lTimer = 0;
	mass = m;
	invMass = 1 / mass;

	if (renderItem) renderItem->release();
	physx::PxShape* sphereShape = CreateShape(physx::PxSphereGeometry(size));
	renderItem = new RenderItem(sphereShape, &pose, Vector4(color.x, color.y, color.z, 1.0f));
	active = true;
}

void Particle::integrateSemiEuler(double t) {
	acc = f * invMass;
	vel = vel + acc * t;
	vel = vel * pow(damping, t);
	pose.p = pose.p + physx::PxVec3(vel * t + acc * 0.5f * t * t);
}

void Particle::changeMass(bool increase) {
	(increase) ? mass += massMod : mass -= massMod;
}

void Particle::countLifeTime(double t) {
	if (!active) return;
	lTimer += t;
	if (lTimer >= lifeTime) {
		active = false;
		lTimer = 0;
	}
}

void Particle::decreaseOpacity(double t) {
	if (!active) return;
	float newOpac = renderItem->color.w - std::powf(t / lifeTime, 9);
	if (newOpac < 0.f) newOpac = 0;
	renderItem->color.w = newOpac;
}

void Particle::decreaseSize(double t) {
	if (!active) return;
	float newSize = renderItem->shape->getGeometry().sphere().radius - (t / lifeTime) * initSize;
	if (newSize < 0) newSize = 0.00001f;
	Vector4 currColor = renderItem->color;

	if (renderItem) renderItem->release();
	physx::PxShape* sphereShape = CreateShape(physx::PxSphereGeometry(newSize));
	renderItem = new RenderItem(sphereShape, &pose, currColor);
}