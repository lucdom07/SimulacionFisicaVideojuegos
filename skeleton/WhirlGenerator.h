#pragma once
#include <vector>
#include "ForceGenerator.h"
#include "WindGenerator.h"
class WhirlGenerator : public WindGenerator
{
public:
    WhirlGenerator(Vector3D dimArea, Vector3D centerPos, float k) : WindGenerator(dimArea, centerPos, Vector3D(), k) {};
    ~WhirlGenerator() {};
    void updateForce(Particle* particle, float dt) override;
};

