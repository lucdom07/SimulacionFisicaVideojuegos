#include <iostream>
#include "Particle.h"
#include "RenderUtils.hpp"

Particle::Particle() : active(false), pose(physx::PxTransform(physx::PxVec3(Vector3D(0,0,0)))), lastPose(Vector3D(0, 0, 0)), 
	vel(Vector3D(0, 0, 0)), acc(Vector3D(0, 0, 0)), mass(0.f), gravity(Vector3D(0, 0, 0)), lifeTime(0), lTimer(0), initSize(0.f) {
	physx::PxShape* sphereShape = CreateShape(physx::PxSphereGeometry(0.1f));
	renderItem = new RenderItem(sphereShape, &pose, Vector4(0.f, 0.f, 0.f, 0.f));
};

Particle::Particle(Vector3D pos, Vector3D pvel, Vector3D a, Vector3D color, float m, float g, float life, float size) :
	active(true), pose(physx::PxTransform(physx::PxVec3(pos))), lastPose(pos), vel(pvel), acc(a), 
	lifeTime(life), lTimer(0), initSize(size) {
	mass = m * std::powf((pvel.magnitude() / pvel.magnitude() * simVelMod), 2.f);
	float simGrav = g * std::powf(pvel.magnitude() * simVelMod / pvel.magnitude(), 2.f);
	gravity = Vector3D(0, -simGrav, 0);
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
	integrateSemiEuler(dt);
	decreaseOpacity(dt);
	decreaseSize(dt);
}

void Particle::configParticle(Vector3D pos, Vector3D pvel, Vector3D a, Vector3D color, float m, float g, float life, float size) {
	pose = physx::PxTransform(physx::PxVec3(pos));
	lastPose = pos;
	vel = pvel; 
	acc = a;
	initSize = size;
	lifeTime = life; 
	lTimer = 0;

	mass = m * std::powf((pvel.magnitude() / pvel.magnitude() * simVelMod), 2.f);
	float simGrav = g * std::powf(pvel.magnitude() * simVelMod / pvel.magnitude(), 2.f);
	gravity = Vector3D(0, -simGrav, 0);

	if (renderItem) renderItem->release();
	physx::PxShape* sphereShape = CreateShape(physx::PxSphereGeometry(size));
	renderItem = new RenderItem(sphereShape, &pose, Vector4(color.x, color.y, color.z, 1.0f));
	active = true;
}

void Particle::integrateEuler(double t) {
	pose.p = pose.p + physx::PxVec3(vel) * t;
	vel = vel + acc * t;
	vel = vel * pow(damping, t); // para que el damping dependa del tiempo
}

void Particle::integrateSemiEuler(double t) {
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