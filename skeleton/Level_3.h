#pragma once
#include "Scene.h"
#include "RenderUtils.hpp"
#include "ParticleSystem.h"
#include "ParticleGenerator.h"
#include "WhirlGenerator.h"
#include "ExplosionGenerator.h"

class Level_3 :
    public Scene
{
public:
    explicit Level_3(std::string name) : Scene(std::move(name)) {}

    void init() override {
        // CREACIÓN SISTEMAS DE PARTÍCULAS
        GeneratorConfig config;
        config = {
            GAUSSIAN, //Tipo de distribución
            UniformConfig{ // Configuración distribución uniforme
            },
            GaussianConfig{ // Configuración distribución gaussiana
                Vector3D(0.f, 0.f, 0.f), Vector3D(0.0001f, 0.0001f, 0.0001f), // dirección velocidad
                0.f, 0.0001f, //magnitud velocidad
                15.f, 0.5f, //vida
                1.f, 0.5f, //tamaño
                1.f, 0.1f, // color rojo
                0.3f, 0.1f, //color verde
                0.1f, 0.1f // color azul
            },
            Vector3D(0.f,1.f,0.f),
            1000.f, // masa
            0.2f, // tiempo de generación
            5, // media partículas
            3, // varianza partículas
            1.f, //radio de emisión
            physx::PxTransform(Vector3(0,0,0)) //transform del emisor
        };
        partSys.push_back(new ParticleSystem());
        ParticleGenerator* partGen = new ParticleGenerator(config);
        partSys[0]->addParticleGen(partGen);
        //WhirlGenerator* whirl = new WhirlGenerator(Vector3D(15.f, 40.f, 15.f), Vector3D(0.f, 40.f, 0.f), 40.f);
        //partSys[0]->addForce(whirl);
        ExplosionGenerator* exp = new ExplosionGenerator(Vector3D(40.f, 40.f, 40.f), Vector3D(-20.f, 0.f, -20.f), 40.f, 40.f, 10.f);
        partSys[0]->addForce(exp);
        forces.push_back(exp);
    }

    void update(double dt) override {
        for (ParticleSystem* s : partSys) {
            s->update(dt);
        }
    }

    void keyPress(unsigned char key, const physx::PxTransform& camera) override {
    }

    void cleanup() override {
        for (ParticleSystem* s : partSys) {
            delete s;
        }
        for (ForceGenerator* f : forces) {
            delete f;
        }
    }
private:
    std::vector<ParticleSystem*> partSys;
    std::vector<ForceGenerator*> forces;
};

