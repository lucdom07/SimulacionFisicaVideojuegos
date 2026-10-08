#include <iostream>
#include "Bullet.h"

Bullet::Bullet(Vector3D pos, Vector3D simvel, float rvel, Vector3D a, float d, float rMass, float rGravity) :
	Particle(pos, simvel, a, d, rMass) {
	mass = rMass * std::powf((rvel/simvel.magnitude()), 2.f);
	float simGrav = rGravity * std::powf(simvel.magnitude() / rvel, 2.f);
	gravity = Vector3D(0, -simGrav, 0);
};

void Bullet::integrateSemiEuler(double t) {
	vel = vel + gravity * mass * t;
	vel = vel * pow(damping, t);
	pose.p = pose.p + physx::PxVec3(vel * t + gravity * mass * 0.5f * t * t);
}

void Bullet::changeGravity(bool increase) {
	(increase) ? gravity -= Vector3D(0, gravMod, 0) : gravity += Vector3D(0, gravMod, 0);
}