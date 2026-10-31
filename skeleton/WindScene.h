#pragma once
#include "Scene.h"
#include "RenderUtils.hpp"
#include "ParticleSystem.h"
#include "ParticleGenConfigs.h"
#include "WindGenerator.h"
class WindScene :
    public Scene
{
public:
    explicit WindScene(std::string name) : Scene(std::move(name)) {}

    void init() override {
        // CREACIÓN SISTEMAS DE PARTÍCULAS
        GeneratorConfig config;
        config = {
            GAUSSIAN, //Tipo de distribución
            UniformConfig{ // Configuración distribución uniforme
            },
            GaussianConfig{ // Configuración distribución gaussiana
                Vector3D(0.f, 1.f, 0.f), Vector3D(0.05f, 0.0001f, 0.05f), // dirección velocidad
                15.f, 5.f, //magnitud velocidad
                15.f, 0.5f, //vida
                1.f, 0.5f, //tamaño
                1.f, 0.1f, // color rojo
                0.3f, 0.1f, //color verde
                0.1f, 0.1f // color azul
            },
            Vector3D(0.f,1.f,0.f),
            1000.f, // masa
            1.f, // tiempo de generación
            1, // media partículas
            1, // varianza partículas
            2.f, //radio de emisión
            physx::PxTransform(Vector3(0,0,0)) //transform del emisor
        };
        partSys.push_back(new ParticleSystem(config));
        WindGenerator* wind = new WindGenerator(Vector3D(10.f, 10.f, 10.f), Vector3D(0.f, 20.f, 0.f), Vector3D(1000.f, 0.f, 0.f), 7.f);
        partSys[0]->addForce(wind);
        forces.push_back(wind);
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