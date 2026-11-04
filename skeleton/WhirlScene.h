#pragma once
#include "Scene.h"
#include "RenderUtils.hpp"
#include "ParticleSystem.h"
#include "ParticleGenerator.h"
#include "WhirlGenerator.h"
class WhirlScene :
    public Scene
{
public:
    explicit WhirlScene(std::string name) : Scene(std::move(name)) {}

    void init() override {
        // CREACIÓN SISTEMAS DE PARTÍCULAS
        GeneratorConfig config;
        config = {
            GAUSSIAN, //Tipo de distribución
            UniformConfig{ // Configuración distribución uniforme
            },
            GaussianConfig{ // Configuración distribución gaussiana
                Vector3D(0.f, 1.f, 0.f), Vector3D(0.2f, 0.0001f, 0.2f), // dirección velocidad
                10.f, 5.f, //magnitud velocidad
                15.f, 0.5f, //vida
                1.f, 0.5f, //tamaño
                1.f, 0.1f, // color rojo
                0.3f, 0.1f, //color verde
                0.1f, 0.1f // color azul
            },
            Vector3D(0.f,1.f,0.f),
            200.f, // masa
            0.5f, // tiempo de generación
            20, // media partículas
            1, // varianza partículas
            2.f, //radio de emisión
            physx::PxTransform(Vector3(0,0,0)) //transform del emisor
        };
        partSys = new ParticleSystem();
        partSys->addParticleGen(new ParticleGenerator(config));
        WhirlGenerator* whirl = new WhirlGenerator(Vector3D(50.f, 50.f, 50.f), Vector3D(0.f, 0.f, 0.f), 10.f);
        partSys->addForce(whirl);
        forces.push_back(whirl);
    }

    void update(double dt) override {
        partSys->update(dt);
    }

    void keyPress(unsigned char key, const physx::PxTransform& camera) override {
    }

    void cleanup() override {
        delete partSys;
        for (ForceGenerator* f : forces) {
            delete f;
        }
    }
private:
    ParticleSystem* partSys;
    std::vector<ForceGenerator*> forces;
};

