#pragma once
#include <vector>
#include <iostream>
#include "Scene.h"
#include "RenderUtils.hpp"
#include "ParticleSystem.h"
#include "ParticleGenConfigs.h"
class P2_Scene :
    public Scene
{
public:
    explicit P2_Scene(std::string name) : Scene(std::move(name)), particleSys(nullptr) {}

    void init() override {
        GeneratorConfig config{
            UNIFORM,
            UniformConfig{
                5.f, 15.f,
                5.f, 15.f,
                7.f, 15.f,
                0.1f, 1.f,
                0.1f, 1.f,
                0.1f, 1.f
            },
            GaussianConfig{},
            Vector3D(0.f,1.f,0.f),
            10.f,
            0.3f,
            20,
            10,
            100.f,
            physx::PxTransform(Vector3(0,0,0))
        };
        particleSys = new ParticleSystem(config);
    }

    void update(double dt) override {
        particleSys->update(dt);
    }

    void keyPress(unsigned char key, const physx::PxTransform& camera) override {
    }

    void cleanup() override {
        delete particleSys;
    }

private:
    ParticleSystem* particleSys;
};

