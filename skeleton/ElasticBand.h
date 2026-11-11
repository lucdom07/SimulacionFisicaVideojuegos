#pragma once
#include "SpringGenerator.h"
class ElasticBand :
    public SpringGenerator
{
public:
    ElasticBand(double k, double rLength, Particle* other);
    ~ElasticBand() {};
    void updateForce(Particle* particle, float dt) override;
};

