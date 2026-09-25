#pragma once
#include <cmath>
#include <PxPhysicsAPI.h>
class Vector3D {
public:
	float x, y, z;
	Vector3D() : x(0), y(0), z(0) {}
	Vector3D(float vx, float vy, float vz) : x(vx), y(vy), z(vz) {}

	float magnitude() const {
		return sqrt(x*x + y*y + z*z);
	};

	Vector3D normalize() const {
		float m = magnitude();
		return Vector3D(this->x/m, this->y/m, this->z/m);
	};

	//producto escalar
	float dot(const Vector3D& v) const {
		return this->x * v.x + this->y * v.y + this->z * v.z;
	};

	//producto vectorial
	Vector3D cross(const Vector3D& v) const {
		return Vector3D(this->y * v.z - this->z * v.y, this->z * v.x - this->x * v.z, this->x * v.y - this->y * v.x);
	};

	Vector3D& operator=(const Vector3D& v) {
		if (&v == this) return *this;
		this->x = v.x;
		this->y = v.y;
		this->z = v.z;
		return *this;
	};

	Vector3D& operator+(const Vector3D& v) {
		return Vector3D(this->x + v.x, this->y + v.y, this->z + v.z);
	};

	Vector3D& operator-(const Vector3D& v) {
		return Vector3D(this->x - v.x, this->y - v.y, this->z - v.z);
	};

	Vector3D& operator*(float s) {
		return Vector3D(this->x * s, this->y * s, this->z * s);
	};

	Vector3D& operator+=(const Vector3D& v) {
		this->x += v.x;
		this->y += v.y;
		this->z += v.z;
		return *this;
	};

	explicit operator physx::PxVec3() const {
		return physx::PxVec3(this->x, this->y, this->z);
	}

	Vector3D& operator=(const physx::PxVec3& v) {
		this->x = v.x;
		this->y = v.y;
		this->z = v.z;
		return *this;
	};
};