#include <iostream>
#include "Bullet.h"


// A la constructora base Particle le pasamos directamente las magnitudes escaladas de masa y velocidad para la simulación
Bullet::Bullet(Vector3D pos, Vector3D rvel, float rMass, float rGravity) :
	Particle(pos, Vector3D(), Vector3D(), Vector3D(1.f, 0.f, 0.f), 0.f, 0.f, -1.f, 10.f) {
	vel = rvel * simVelMod;
	mass = rMass * std::powf((rvel.magnitude() / (rvel * simVelMod).magnitude()), 2.f);
	invMass = 1 / mass;
	simGrav = Vector3D(0, -(rGravity * std::powf((rvel * simVelMod).magnitude() / rvel.magnitude(), 2.f)), 0);
};

void Bullet::integrateSemiEuler(double t) {
	vel = vel + simGrav * invMass * t;
	vel = vel * pow(damping, t);
	pose.p = pose.p + physx::PxVec3(vel * t + simGrav * 0.5f * t * t);
}

void Bullet::changeGravity(bool increase) {
	(increase) ? simGrav.y -= gravMod : simGrav.y += gravMod;
}