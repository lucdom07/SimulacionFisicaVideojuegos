#include <iostream>
#include "Bullet.h"

Bullet::Bullet(Vector3D pos, Vector3D simvel, float rvel, Vector3D a, float d, float rMass, float rGravity) :
	Particle(pos, simvel, a, Vector3D(1.f, 0.f, 0.f), rMass, rGravity, -1, 10.f) {
};