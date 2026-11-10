#pragma once
#include "SpringGenerator.h"
class AnchoredSpring :
    public SpringGenerator
{
public:
    AnchoredSpring(double k, double rest, const Vector3D& anchor);
    ~AnchoredSpring();
};