#pragma once
#include "ForceGenerator.h"
class Particle;
class SpringGenerator :
    public ForceGenerator
{
public:
    SpringGenerator(double k, double rLength, Particle* other);
    virtual ~SpringGenerator() {};
    virtual void updateForce(Particle* particle, float dt) override;
    inline double getK() { return mK; };
    inline void setK(double k) { mK = k; };
protected:
    double mK;
    double mRestLength;
    Particle* mOther;
};