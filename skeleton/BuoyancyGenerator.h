#pragma once
#include "ForceGenerator.h"
class BuoyancyGenerator :
    public ForceGenerator
{
public:
    BuoyancyGenerator(float h, float V, float d);
    ~BuoyancyGenerator();

    float getVolume() { return mVolume; };

    void changeVolume(float v);
    void updateForce(Particle* particle, float dt) override;
protected:
    float mHeight;
    float mVolume;
    float mDensity;
    float mGrav = 9.81;

    Particle* mLiquidPart;
};

