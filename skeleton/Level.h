#pragma once
#include "Scene.h"
#include "RenderUtils.hpp"
#include <vector>
#include <iostream>
#include <unordered_map>
#include "ParticleSystem.h"
#include "ParticleGenerator.h"
#include "WhirlGenerator.h"
#include "ForceRegistry.h"

class Level :
    public Scene
{
public:
    explicit Level(std::string name) : Scene(std::move(name)), partsReg(nullptr) {
    }

    void init() override {
        partsReg = new ForceRegistry();

        // CREACIÓN SISTEMAS DE PARTÍCULAS
        GeneratorConfig water;
        water = {
            GAUSSIAN, //Tipo de distribución
            UniformConfig{ // Configuración distribución uniforme
            },
            GaussianConfig{ // Configuración distribución gaussiana
                Vector3D(-1.f, 0.f, 0.f), Vector3D(0.001f, 0.0001f, 0.001f), // dirección velocidad
                2.f, 0.1f, //magnitud velocidad
                5.f, 0.5f, //vida
                1.f, 0.2f, //tamaño
                0.f, 0.01f, // color rojo
                0.2f, 0.1f, //color verde
                0.9f, 0.1f // color azul
            },
            Vector3D(0.f,1.f,0.f),
            1.f, // masa
            0.4f, // tiempo de generación
            25, // media partículas
            1, // varianza partículas
            10.f, //radio de emisión
            physx::PxTransform(Vector3(-40,0,0)) //transform del emisor
        };
        partSys.push_back(new ParticleSystem());
        partSys[0]->addParticleGen(new ParticleGenerator(water));

        // CREACIÓN FUERZAS
        WhirlGenerator* whirl = new WhirlGenerator(Vector3D(50.f, 50.f, 50.f), Vector3D(-40.f, 0.f, 0.f), 1.f);
        partSys[0]->addForce(whirl);
        forces.push_back(whirl);
    }

    void update(double dt) override {
        for (ParticleSystem* s : partSys) {
            s->update(dt);
        }
        partsReg->applyForce(dt);
    }

    void keyPress(unsigned char key, const physx::PxTransform& camera) override {
    }

    void cleanup() override {
        for (ParticleSystem* p : partSys) {
            delete p;
        }
        for (ForceGenerator* p : forces) {
            delete p;
        }
    }

private:
    std::vector<ParticleSystem*> partSys;
    std::vector<ForceGenerator*> forces;
    ForceRegistry* partsReg;
};

