#include <iostream>
#include "Bullet.h"

// A la constructora base Particle le pasamos directamente las magnitudes escaladas de masa y velocidad para la simulación
Bullet::Bullet(Vector3D pos, Vector3D rvel, float rMass, float rGravity) :
	Particle(pos, rvel* simVelMod, Vector3D(1.f, 0.f, 0.f), rMass * std::powf((rvel.magnitude() / (rvel * simVelMod).magnitude()), 2.f), -1, 10.f),
	simGrav(Vector3D(0, -(rGravity * std::powf((rvel * simVelMod).magnitude() / rvel.magnitude(), 2.f)), 0)) {
};

void Bullet::integrateSemiEuler(double t) {
	vel = vel + simGrav * mass * t;
	vel = vel * pow(damping, t);
	pose.p = pose.p + physx::PxVec3(vel * t + simGrav * mass * 0.5f * t * t);
}