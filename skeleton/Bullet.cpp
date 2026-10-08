#include <iostream>
#include "Bullet.h"

void Bullet::integrateSemiEuler(double t) {
	vel = vel + gravity * mass * t;
	vel = vel * pow(damping, t);
	pose.p = pose.p + physx::PxVec3(vel * t + gravity * mass * 0.5f * t * t);
	std::cout << "miau\n";
}

void Bullet::changeGravity(bool increase) {
	(increase) ? gravity += Vector3D(0, gravMod, 0) : gravity -= Vector3D(0, gravMod, 0);
}