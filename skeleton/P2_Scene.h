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
            UNIFORM, //Tipo de distribución
            UniformConfig{ // Configuración distribución uniforme
                60.f, 70.f, //velocidad
                1.f, 2.f, //vida
                1.f, 2.f, //tamaño
                0.1f, 1.f, // color rojo
                0.1f, 1.f, //color verde
                0.1f, 1.f // color azul
            },
            GaussianConfig{}, // Configuración distribución gaussiana
            Vector3D(0.f,1.f,0.f),
            10.f, // masa
            0.3f, // tiempo de generación
            20, // media partículas
            10, // varianza partículas
            10.f, //radio de emisión
            physx::PxTransform(Vector3(0,0,0)) //transform del emisor
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

