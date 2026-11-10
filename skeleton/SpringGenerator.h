#pragma once
#include "ForceGenerator.h"
class Particle;
class SpringGenerator :
    public ForceGenerator
{
public:
    SpringGenerator(double k, double rLength, Particle* other);
    virtual ~SpringGenerator() {};
    virtual void updateForce(Particle* particle);
    inline void setK(double k) { mK = k; };
protected:
    double mK;
    double mRestLength;
    Particle* mOther;
};