#include "AnchoredSpring.h"

AnchoredSpring::AnchoredSpring(double k, double rest, const Vector3D& anchor) :
SpringGenerator(k, rest, nullptr){
	mOther = new Particle(anchor, Vector3D(), Vector3D(1., 0., 1.), 0.f, -1.f, 3.f, physx::PxGeometryType::eBOX);
}

AnchoredSpring::~AnchoredSpring() {
	delete mOther;
}